HPDF_FreeDoc  (HPDF_Doc  pdf)
{
    HPDF_PTRACE ((" HPDF_FreeDoc\n"));

    if (HPDF_Doc_Validate (pdf)) {
        if (pdf->xref) {
           HPDF_Xref_Free (pdf->xref);
           pdf->xref = NULL;
        }

        if (pdf->font_mgr) {
            HPDF_List_Free (pdf->font_mgr);
            pdf->font_mgr = NULL;
        }

        if (pdf->fontdef_list)
            CleanupFontDefList (pdf);

        HPDF_MemSet(pdf->ttfont_tag, 0, 6);

        pdf->pdf_version = HPDF_VER_13;
        pdf->outlines = NULL;
        pdf->catalog = NULL;
        pdf->root_pages = NULL;
        pdf->cur_pages = NULL;
        pdf->cur_page = NULL;
        pdf->encrypt_on = HPDF_FALSE;
        pdf->cur_page_num = 0;
        pdf->cur_encoder = NULL;
        pdf->def_encoder = NULL;
        pdf->page_per_pages = 0;

        if (pdf->page_list) {
            HPDF_List_Free (pdf->page_list);
            pdf->page_list = NULL;
        }

        pdf->encrypt_dict = NULL;
        pdf->info = NULL;

        HPDF_Error_Reset (&pdf->error);

        if (pdf->stream) {
            HPDF_Stream_Free (pdf->stream);
            pdf->stream = NULL;
        }
    }
}
