parse_font_face_start_font_face_cb (CRDocHandler * a_this,
                                    CRParsingLocation * a_location)
{
        CRStatement *stmt = NULL;
        enum CRStatus status = CR_OK;

        UNUSED(a_location);

        stmt = cr_statement_new_at_font_face_rule (NULL, NULL);
        g_return_if_fail (stmt);

        status = cr_doc_handler_set_ctxt (a_this, stmt);
        g_return_if_fail (status == CR_OK);
}
