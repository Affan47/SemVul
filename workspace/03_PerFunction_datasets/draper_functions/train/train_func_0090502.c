cr_attr_sel_to_string (CRAttrSel const * a_this)
{
        CRAttrSel const *cur = NULL;
        guchar *result = NULL;
        GString *str_buf = NULL;

        g_return_val_if_fail (a_this, NULL);

        str_buf = g_string_new (NULL);

        for (cur = a_this; cur; cur = cur->next) {
                if (cur->prev) {
                        g_string_append_c (str_buf, ' ');
                }

                if (cur->name) {
                        guchar *name = NULL;

                        name = g_strndup (cur->name->stryng->str,
                                          cur->name->stryng->len);
                        if (name) {
                                g_string_append (str_buf, name);
                                g_free (name);
                                name = NULL;
                        }
                }

                if (cur->value) {
                        guchar *value = NULL;

                        value = g_strndup (cur->value->stryng->str,
                                           cur->value->stryng->len);
                        if (value) {
                                switch (cur->match_way) {
                                case SET:
                                        break;

                                case EQUALS:
                                        g_string_append_c (str_buf, '=');
                                        break;

                                case INCLUDES:
                                        g_string_append (str_buf, "~=");
                                        break;

                                case DASHMATCH:
                                        g_string_append (str_buf, "|=");
                                        break;

                                default:
                                        break;
                                }

                                g_string_append_printf
                                        (str_buf, "\"%s\"", value);

                                g_free (value);
                                value = NULL;
                        }
                }
        }

        if (str_buf) {
                result = str_buf->str;
                g_string_free (str_buf, FALSE);
        }

        return result;
}
