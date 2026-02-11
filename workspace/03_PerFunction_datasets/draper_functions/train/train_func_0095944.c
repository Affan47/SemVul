test_cr_declaration_parse_list (void)
{
        GString *str = NULL;
        guchar *tmp_str = NULL;
        CRDeclaration *decl = NULL,
                *cur_decl = NULL;

        decl = cr_declaration_parse_list_from_buf (gv_decl_list_buf,
                                                   CR_UTF_8);
        if (!decl)
                return CR_ERROR;
        str = g_string_new (NULL);
        for (cur_decl = decl; cur_decl; cur_decl = cur_decl->next) {
                tmp_str = cr_declaration_to_string (cur_decl, 2);
                if (tmp_str) {
                        g_string_append_printf (str, "%s;", tmp_str);
                        g_free (tmp_str);
                        tmp_str = NULL;
                }

        }
        if (decl) {
                cr_declaration_destroy (decl);
        }

        if (str) {
                g_string_free (str, TRUE);
                str = NULL;
        }

        return CR_OK;
}
