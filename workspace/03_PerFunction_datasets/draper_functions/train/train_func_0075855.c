ccss_property (CRDocHandler * a_handler, CRString * a_name, CRTerm * a_expr, gboolean a_important)
{
    CSSUserData *user_data;
    gchar *name = NULL;
    size_t len = 0;

    g_return_if_fail (a_handler);

    user_data = (CSSUserData *) a_handler->app_data;

    if (a_name && a_expr && user_data->selector) {
        CRSelector *cur;
        for (cur = user_data->selector; cur; cur = cur->next) {
            if (cur->simple_sel) {
                gchar *selector = (gchar *) cr_simple_sel_to_string (cur->simple_sel);
                if (selector) {
                    gchar *style_name, *style_value;
                    name = (gchar *) cr_string_peek_raw_str (a_name);
                    len = cr_string_peek_raw_str_len (a_name);
                    style_name = g_strndup (name, len);
                    style_value = (gchar *)cr_term_to_string (a_expr);
                    rsvg_css_define_style (user_data->ctx,
                                           selector,
                                           style_name,
                                           style_value,
                                           a_important);
                    g_free (selector);
                    g_free (style_name);
                    g_free (style_value);
                }
            }
        }
    }
}
