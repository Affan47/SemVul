copy_dosum_info(Dosum_info* info_pt)
{
    Dosum_info* new_info = NULL;

    if( info_pt != NULL ){
        new_info = alloc_dosum_info();
        new_info->entry = info_pt->entry;
        new_info->kind = info_pt->kind;
        new_info->ope = info_pt->ope;
        new_info->intfunc_entry = info_pt->intfunc_entry;
        new_info->qr_sum = NULL;
        new_info->next = NULL;
    }
    return(new_info);
}
