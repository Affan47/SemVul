bm_get_global_parameter_location(BuzzMachine *bm,int index) {
    void *res=NULL;

    if(!(index<bm->machine_info->numGlobalParameters)) return(0);
    if(!(bm->machine_iface->GlobalVals)) return(0);

    byte *ptr=(byte *)bm->machine_iface->GlobalVals;
    if(!ptr) {
      DBG(" -> machine->GlobalVals is NULL!\n");
    }


    for(int i=0;i<=index;i++) {
        switch(bm->machine_info->Parameters[i]->Type) {
            case pt_note:
            case pt_switch:
            case pt_byte:
                if(i==index) res=(void *)ptr;
                else ptr++;
                break;
            case pt_word:
                if(i==index) res=(void *)ptr;
                else ptr+=2;
                break;
        }
    }
    return(res);
}
