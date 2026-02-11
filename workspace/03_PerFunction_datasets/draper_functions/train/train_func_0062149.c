cr_enc_handler_resolve_enc_alias (const guchar * a_alias_name,
                                  enum CREncoding *a_enc)
{
        gulong i = 0;
        enum CRStatus status = CR_ENCODING_NOT_FOUND_ERROR;

        g_return_val_if_fail (a_alias_name != NULL, CR_BAD_PARAM_ERROR);

        gchar *alias_name_up = g_strdup ((gchar *)a_alias_name);
        g_ascii_strup (alias_name_up, -1);

        for (i = 0; gv_default_aliases[i].name; i++) {
                if (!strcmp (gv_default_aliases[i].name, alias_name_up)) {
                        *a_enc = gv_default_aliases[i].encoding;
                        status = CR_OK;
                        break;
                }
        }

        return status;
}
