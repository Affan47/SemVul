set_prop_display_from_value (CRStyle * a_style, CRTerm * a_value)
{
        static const struct CRPropDisplayValPair disp_vals_map[] = {
                {"none", DISPLAY_NONE},
                {"inline", DISPLAY_INLINE},
                {"block", DISPLAY_BLOCK},
                {"run-in", DISPLAY_RUN_IN},
                {"compact", DISPLAY_COMPACT},
                {"marker", DISPLAY_MARKER},
                {"table", DISPLAY_TABLE},
                {"inline-table", DISPLAY_INLINE_TABLE},
                {"table-row-group", DISPLAY_TABLE_ROW_GROUP},
                {"table-header-group", DISPLAY_TABLE_HEADER_GROUP},
                {"table-footer-group", DISPLAY_TABLE_FOOTER_GROUP},
                {"table-row", DISPLAY_TABLE_ROW},
                {"table-column-group", DISPLAY_TABLE_COLUMN_GROUP},
                {"table-column", DISPLAY_TABLE_COLUMN},
                {"table-cell", DISPLAY_TABLE_CELL},
                {"table-caption", DISPLAY_TABLE_CAPTION},
                {"inherit", DISPLAY_INHERIT},
                {NULL, DISPLAY_NONE}
        };

        g_return_val_if_fail (a_style && a_value, CR_BAD_PARAM_ERROR);

        switch (a_value->type) {
        case TERM_IDENT:
                {
                        int i = 0;

                        if (!a_value->content.str
                            || !a_value->content.str->stryng
                            || !a_value->content.str->stryng->str)
                                break;

                        for (i = 0; disp_vals_map[i].prop_name; i++) {
                                if (!strncmp
                                    (disp_vals_map[i].prop_name,
                                     a_value->content.str->stryng->str,
                                     strlen (disp_vals_map[i].prop_name))) {
                                        a_style->display =
                                                disp_vals_map[i].type;
                                        break;
                                }
                        }
                }
                break;

        default:
                break;
        }

        return CR_OK;
}
