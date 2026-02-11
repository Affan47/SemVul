MG_alignment_vars_callback(AW_root *aw_root,GBDATA *gbd, long ali_nr)
{
    char buffer[256];

    GB_push_transaction(gbd);
    sprintf(buffer,"tmp/merge%li/alignment_name",ali_nr);
    char    *use = aw_root->awar(buffer)->read_string();
    GBDATA *ali_cont = GBT_get_alignment(gbd,use);
    if (!ali_cont) {
        sprintf(buffer,"tmp/merge%li/alignment_type",ali_nr);
        aw_root->awar(buffer)->unmap();

        sprintf(buffer,"tmp/merge%li/alignment_len",ali_nr);
        aw_root->awar(buffer)->unmap();

        sprintf(buffer,"tmp/merge%li/aligned",ali_nr);
        aw_root->awar(buffer)->unmap();

        sprintf(buffer,"tmp/merge%li/security",ali_nr);
        aw_root->awar(buffer)->unmap();
    }else{

        GBDATA *ali_len      = GB_entry(ali_cont,"alignment_len");
        GBDATA *ali_aligned  = GB_entry(ali_cont,"aligned");
        GBDATA *ali_type     = GB_entry(ali_cont,"alignment_type");
        GBDATA *ali_security = GB_entry(ali_cont,"alignment_write_security");

        sprintf(buffer,"tmp/merge%li/alignment_type",ali_nr);
        aw_root->awar(buffer)->map(ali_type);

        sprintf(buffer,"tmp/merge%li/alignment_len",ali_nr);
        aw_root->awar(buffer)->map(ali_len);

        sprintf(buffer,"tmp/merge%li/aligned",ali_nr);
        aw_root->awar(buffer)->map(ali_aligned);

        sprintf(buffer,"tmp/merge%li/security",ali_nr);
        aw_root->awar(buffer)->map(ali_security);

    }
    GB_pop_transaction(gbd);
    free(use);
}
