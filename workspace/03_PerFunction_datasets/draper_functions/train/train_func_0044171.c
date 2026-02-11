dump_config(jk_ws_service_t *s,
                       status_endpoint_t *p,
                       int mime, jk_logger_t *l)
{
    status_worker_t *w = p->worker;
    jk_worker_env_t *we = w->we;
    jk_map_t *init_data = we->init_data;

    JK_TRACE_ENTER(l);

    if (init_data) {
        int l = jk_map_size(init_data);
        int i;
        if (mime == JK_STATUS_MIME_HTML) {
            jk_puts(s, "<hr/><h2>Configuration Data</h2><hr/>\n");
            jk_puts(s, "This dump does not include any changes applied by the status worker\n");
            jk_puts(s, "to the configuration after the initial startup\n");
            jk_puts(s, "<PRE>\n");
        }
        else if (mime == JK_STATUS_MIME_XML) {
            jk_print_xml_start_elt(s, w, 2, 0, "configuration");
        }
        else if (mime == JK_STATUS_MIME_TXT) {
            jk_puts(s, "Configuration:\n");
        }
        for (i=0;i<l;i++) {
            const char *name = jk_map_name_at(init_data, i);
            if (name) {
                const char *value;
                size_t nl = strlen(name);
                if (nl > sizeof(".secret") &&
                    strcmp(name + nl - 7, ".secret") == 0) {
                    continue;
                }
                value = jk_map_value_at(init_data, i);
                if (!value)
                    value = "(null)";
                if (mime == JK_STATUS_MIME_HTML ||
                    mime == JK_STATUS_MIME_PROP ||
                    mime == JK_STATUS_MIME_TXT) {
                    jk_putv(s, name, "=", value, "\n", NULL);
                }
                else if (mime == JK_STATUS_MIME_XML) {
                     jk_print_xml_att_string(s, 4, name, value);
                }
            }
        }
        if (mime == JK_STATUS_MIME_HTML) {
            jk_puts(s, "</PRE>\n");
        }
        else if (mime == JK_STATUS_MIME_XML) {
            jk_print_xml_stop_elt(s, 2, 1);
        }
    }
    else {
        JK_TRACE_EXIT(l);
        return JK_FALSE;
    }

    JK_TRACE_EXIT(l);
    return JK_TRUE;
}
