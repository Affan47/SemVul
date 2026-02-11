cr_statement_media_rule_to_string (CRStatement const *a_this,
                                   gulong a_indent)
{
        gchar *str = NULL ;
        GString *stringue = NULL ;
        GList const *cur = NULL;

        g_return_val_if_fail (a_this->type == AT_MEDIA_RULE_STMT,
                              NULL);

        if (a_this->kind.media_rule) {
                stringue = g_string_new (NULL) ;
                cr_utils_dump_n_chars2 (' ', stringue, a_indent);
                g_string_append (stringue, "@media");

                for (cur = a_this->kind.media_rule->media_list; cur;
                     cur = cur->next) {
                        if (cur->data) {
                                guchar *str = cr_string_dup2
                                        ((CRString const *) cur->data);

                                if (str) {
                                        if (cur->prev) {
                                                g_string_append
                                                        (stringue,
                                                         ",");
                                        }
                                        g_string_append_printf
                                                (stringue,
                                                 " %s", str);
                                        g_free (str);
                                        str = NULL;
                                }
                        }
                }
                g_string_append (stringue, " {\n");
                str = cr_statement_list_to_string
                        (a_this->kind.media_rule->rulesets,
                         a_indent + DECLARATION_INDENT_NB) ;
                if (str) {
                        g_string_append (stringue, str) ;
                        g_free (str) ;
                        str = NULL ;
                }
                g_string_append (stringue, "\n}");
        }
        if (stringue) {
                str = stringue->str ;
                g_string_free (stringue, FALSE) ;
        }
        return str ;
}
