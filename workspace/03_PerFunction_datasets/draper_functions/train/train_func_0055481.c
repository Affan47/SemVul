GetPageCount  (HPDF_Dict    pages)
{
    HPDF_UINT i;
    HPDF_UINT count = 0;
    HPDF_Array kids = (HPDF_Array)HPDF_Dict_GetItem (pages, "Kids",
            HPDF_OCLASS_ARRAY);

    HPDF_PTRACE((" GetPageCount\n"));

    if (!kids)
        return 0;

    for (i = 0; i < kids->list->count; i++) {
        void *obj = HPDF_Array_GetItem (kids, i, HPDF_OCLASS_DICT);
        HPDF_Obj_Header *header = (HPDF_Obj_Header *)obj;

        if (header->obj_class == (HPDF_OCLASS_DICT | HPDF_OSUBCLASS_PAGES))
            count += GetPageCount ((HPDF_Dict)obj);
        else if (header->obj_class == (HPDF_OCLASS_DICT | HPDF_OSUBCLASS_PAGE))
            count += 1;
    }

    return count;
}
