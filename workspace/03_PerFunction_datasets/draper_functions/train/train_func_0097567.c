free_stasche_syncs_table(Stasche_syncs_table *syncspt){

    if(syncspt!=NULL){
      if(syncspt->pc!=NULL) destruct_IntSet(syncspt->pc);
      free(syncspt);
    }
}
