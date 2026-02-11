FreeFontDefList  (HPDF_Doc   pdf)
{
    HPDF_List list = pdf->fontdef_list;
    HPDF_UINT i;

    HPDF_PTRACE ((" HPDF_Doc_FreeFontDefList\n"));

    for (i = 0; i < list->count; i++) {
        HPDF_FontDef def = (HPDF_FontDef)HPDF_List_ItemAt (list, i);

        HPDF_FontDef_Free (def);
    }

    HPDF_List_Free (list);

    pdf->fontdef_list = NULL;
}
