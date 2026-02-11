HPDF_Page_New_Content_Stream  (HPDF_Page page,
                               HPDF_Dict* new_stream)
{


    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    HPDF_PageAttr attr;
    HPDF_UINT filter;
    HPDF_Array contents_array;

    HPDF_PTRACE((" HPDF_Page_New_Content_Stream\n"));

    attr = (HPDF_PageAttr)page->attr;
    filter = attr->contents->filter;


    contents_array = (HPDF_Array) HPDF_Dict_GetItem(page,"Contents", HPDF_OCLASS_ARRAY);
    if (!contents_array) {
        HPDF_Error_Reset (page->error);


        contents_array = HPDF_Array_New(page->mmgr);
        if (!contents_array)
            return HPDF_Error_GetCode (page->error);
        ret += HPDF_Array_Add(contents_array,attr->contents);
        ret += HPDF_Dict_Add (page, "Contents", contents_array);
    }


    attr->contents = HPDF_DictStream_New (page->mmgr, attr->xref);
    attr->contents->filter = filter;
    attr->stream = attr->contents->stream;

    if (!attr->contents)
        return HPDF_Error_GetCode (page->error);

    ret += HPDF_Array_Add (contents_array,attr->contents);


    if (ret == HPDF_OK && new_stream != NULL)
        *new_stream = attr->contents;

    return ret;
}
