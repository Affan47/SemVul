splr_entry_changed(GtkEditable *editable, GtkWidget *spl_window) {
    Itdb_SPLRule *splr;
    gchar *str;
    time_t t;
    enum entrytype type;

    g_return_if_fail (spl_window);
    splr = g_object_get_data(G_OBJECT (editable), "spl_rule");
    g_return_if_fail (splr);
    type = (enum entrytype) g_object_get_data(G_OBJECT (editable), "spl_entrytype");
    g_return_if_fail (type != 0);

    str = gtk_editable_get_chars(editable, 0, -1);
    switch (type) {
    case spl_ET_FROMVALUE:
        switch (splr->field) {
        case ITDB_SPLFIELD_RATING:
            splr->fromvalue = ITDB_RATING_STEP * atol(str);
            break;
        case ITDB_SPLFIELD_TIME:
            splr->fromvalue = 1000 * strtod(str, NULL);
            break;
        default:
            splr->fromvalue = atol(str);
            break;
        }
        break;
    case spl_ET_FROMVALUE_DATE:
        t = time_string_to_fromtime(str);
        if (t != -1)
            splr->fromvalue = t;
        break;
    case spl_ET_FROMDATE:
        splr->fromdate = atol(str);
        break;
    case spl_ET_TOVALUE:
        switch (splr->field) {
        case ITDB_SPLFIELD_RATING:
            splr->tovalue = ITDB_RATING_STEP * atol(str);
            break;
        case ITDB_SPLFIELD_TIME:
            splr->tovalue = 1000 * strtod(str, NULL);
            break;
        default:
            splr->tovalue = atol(str);
            break;
        }
        break;
    case spl_ET_TOVALUE_DATE:
        t = time_string_to_totime(str);
        if (t != -1)
            splr->tovalue = t;
        break;
    case spl_ET_TODATE:
        splr->todate = atol(str);
        break;
    case spl_ET_INTHELAST:
        splr->fromdate = -atol(str);
        break;
    case spl_ET_STRING:
        g_free(splr->string);
        splr->string = g_strdup(str);
        break;
    default:

        g_free(str);
        g_return_if_fail (FALSE);
        break;
    }
    g_free(str);
}
