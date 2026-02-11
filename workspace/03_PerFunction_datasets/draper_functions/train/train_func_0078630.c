get_single_realization(
bool check_time_,
Int4 M_min_,
Int4 nalp_,
bool killing_flag_,
Int4 level_,
Int4 diff_opt_,
alp *&obj_,
bool &sucess_flag_,
double &d_eps_)
{
        if(!obj_)
        {
                obj_=new alp(d_alp_data);
                alp_data::assert_mem(obj_);
                d_alp_data->d_memory_size_in_MB+=sizeof(alp)/mb_bytes;
        };
        obj_->d_single_realiztion_calculation_flag=true;
        obj_->d_check_time_flag=check_time_;

        d_eps_=d_alp_data->Tmin(d_alp_data->d_eps_K,d_alp_data->d_eps_lambda);


        alp*&obj=obj_;

        obj->d_diff_opt=diff_opt_;

        obj->d_sentinels_flag=d_alp_data->d_sentinels_flag;

        sucess_flag_=true;

        while(obj->d_nalp<nalp_)
        {
                obj->simulate_next_alp();
                if(!obj->d_success)
                {
                        sucess_flag_=false;
                        delete obj_;obj_=NULL;
                        d_eps_=d_alp_data->d_eps_lambda;
                        d_alp_data->d_memory_size_in_MB-=sizeof(alp)/mb_bytes;
                        return;
                };
        };


        if(killing_flag_)
        {
                obj->kill_upto_level(M_min_,level_);
                if(!obj->d_success)
                {
                        sucess_flag_=false;
                        delete obj_;obj_=NULL;
                        d_eps_=d_alp_data->d_eps_K;
                        d_alp_data->d_memory_size_in_MB-=sizeof(alp)/mb_bytes;
                        return;
                };
        };

}
