HPDF_List_New  (HPDF_MMgr  mmgr,
                HPDF_UINT  items_per_block)
{
    HPDF_List list;

    HPDF_PTRACE((" HPDF_List_New\n"));

    if (mmgr == NULL)
        return NULL;

    list = (HPDF_List)HPDF_GetMem (mmgr, sizeof(HPDF_List_Rec));
    if (list) {
        list->mmgr = mmgr;
        list->error = mmgr->error;
        list->block_siz = 0;
        list->items_per_block =
            (items_per_block <= 0 ? HPDF_DEF_ITEMS_PER_BLOCK : items_per_block);
        list->count = 0;
        list->obj = NULL;
    }

    return list;
}
