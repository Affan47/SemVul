cr_sel_eng_get_matched_rulesets (CRSelEng * a_this,
                                 CRStyleSheet * a_sheet,
                                 xmlNode * a_node,
                                 CRStatement *** a_rulesets, gulong * a_len)
{
        CRStatement **stmts_tab = NULL;
        enum CRStatus status = CR_OK;
        gulong tab_size = 0,
                tab_len = 0,
                index = 0;
        gushort stmts_chunck_size = 8;

        g_return_val_if_fail (a_this
                              && a_sheet
                              && a_node
                              && a_rulesets && *a_rulesets == NULL
                              && a_len, CR_BAD_PARAM_ERROR);

        stmts_tab = g_try_malloc (stmts_chunck_size * sizeof (CRStatement *));

        if (!stmts_tab) {
                cr_utils_trace_info ("Out of memory");
                status = CR_ERROR;
                goto error;
        }
        memset (stmts_tab, 0, stmts_chunck_size * sizeof (CRStatement *));

        tab_size = stmts_chunck_size;
        tab_len = tab_size;

        while ((status = cr_sel_eng_get_matched_rulesets_real
                (a_this, a_sheet, a_node, stmts_tab + index, &tab_len))
               == CR_OUTPUT_TOO_SHORT_ERROR) {
                stmts_tab = g_try_realloc (stmts_tab,
                                           (tab_size + stmts_chunck_size)
                                           * sizeof (CRStatement *));
                if (!stmts_tab) {
                        cr_utils_trace_info ("Out of memory");
                        status = CR_ERROR;
                        goto error;
                }
                tab_size += stmts_chunck_size;
                index += tab_len;
                tab_len = tab_size - index;
        }

        tab_len = tab_size - stmts_chunck_size + tab_len;
        *a_rulesets = stmts_tab;
        *a_len = tab_len;

        return CR_OK;

      error:

        if (stmts_tab) {
                g_free (stmts_tab);
                stmts_tab = NULL;

        }

        *a_len = 0;
        return status;
}
