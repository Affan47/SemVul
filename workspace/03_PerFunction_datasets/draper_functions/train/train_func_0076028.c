awt_arbdb_scanner_delete(void *dummy, struct adawcbstruct *cbs)
{
    AWUSE(dummy);
    GBDATA *gbd = awt_get_arbdb_scanner_gbd_and_begin_trans((AW_CL)cbs);
    if (!gbd) {
        aw_message("Sorry, cannot perform your operation, please redo it");
    }else if (awt_check_scanner_key_data(cbs,gbd)) {
        ;
    }else{
        GB_ERROR error = GB_delete(gbd);
        if (error) aw_message((char *)error);
    }
    GB_commit_transaction(cbs->gb_main);
}
