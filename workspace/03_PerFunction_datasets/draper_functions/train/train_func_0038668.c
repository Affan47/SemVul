get_max_hmt_no()
{
    Module_table *mpt = NULL;
    int  hmt_no;
    int  max = -1;

    for (mpt = module_head; mpt != NULL; mpt = mpt->next){
        if (mpt->super_hmdf) {
            hmt_no = get_max_hmt_no_of_module(mpt->super_hmdf);
            if (hmt_no > max){
                max = hmt_no;
            }
        }
    }
    return  max;
}
