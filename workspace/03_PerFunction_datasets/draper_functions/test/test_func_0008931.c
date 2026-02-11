check_global_view_of_subgroups( int n_procs_selected,
        int n_procs_in, int ll_p1, int* all_selected,
        mca_sbgp_base_module_t *module )
{

    int ret=OMPI_SUCCESS;
    int i, sum;

    bool local_leader_found=false;


    for (i = 0; i < n_procs_selected; i++) {
        if( ll_p1 == -all_selected[module->group_list[i]]) {

            if( local_leader_found ) {


                ML_VERBOSE(0, ("More than a single leader for a group.\n"));
                ret=OMPI_ERROR;
                goto ERROR;
            } else {
                local_leader_found=true;
            }
        }
    }


    sum=0;
    for (i = 0; i < n_procs_in; i++) {
        if(ll_p1==all_selected[i]) {
            sum++;
        } else if( ll_p1 == -all_selected[i]) {
            sum++;
        }
    }
    if( sum != n_procs_selected ) {
        fprintf(stderr,"n procs in %d\n",n_procs_in);
        ML_VERBOSE(0, ("number of procs in the group unexpeted.  Expected %d Got %d\n",n_procs_selected,sum));
        ret=OMPI_ERROR;
        goto ERROR;
    }


    for (i = 0; i < n_procs_selected; i++) {
        if(ll_p1!=all_selected[module->group_list[i]] &&
                ll_p1!=-all_selected[module->group_list[i]] ) {
            ret=OMPI_ERROR;
            ML_VERBOSE(0, ("Mismatch in rank list - element #%d - %d \n",i,all_selected[module->group_list[i]]));
            goto ERROR;
        }
    }


    return ret;

ERROR:

    return ret;
}
