free_stasche_table(Stasche_table *stapt){

    int  i;
    if(stapt!=NULL){
      for(i=0;i<stapt->mts_num;i++){
	free_stasche_mts_table(*(stapt->mts +i));
      }
      free_stasche_mts_info(stapt->mts_info,stapt->mts_num);
      free(stapt);
    }
}
