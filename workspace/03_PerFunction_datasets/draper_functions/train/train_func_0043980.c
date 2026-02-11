add_debug_message (const gchar *datetime,
                           const gchar *source,
                           sat_log_level_t debug_level,
                           const char *message)
{
    guint        total;
    gchar       *str;
    GtkTreeIter  item;


    if (!g_ascii_strcasecmp (source, "1")) {
        hamlibs++;
        str = g_strdup_printf ("%d", hamlibs);
        gtk_label_set_text (GTK_LABEL (hamliblabel), str);
        g_free (str);
        str = g_strdup ("HAMLIB");
    }
    else if (!g_ascii_strcasecmp (source, "2")) {
        gpredicts++;
        str = g_strdup_printf ("%d", gpredicts);
        gtk_label_set_text (GTK_LABEL (gpredictlabel), str);
        g_free (str);
        str = g_strdup ("GPREDICT");
    }
    else {
        others++;
        str = g_strdup_printf ("%d", others);
        gtk_label_set_text (GTK_LABEL (otherlabel), str);
        g_free (str);
        str = g_strdup ("OTHER");
    }

    gtk_list_store_append (GTK_LIST_STORE (model), &item);
    gtk_list_store_set (GTK_LIST_STORE (model), &item,
                        MSG_LIST_COL_TIME, datetime,
                        MSG_LIST_COL_SOURCE, str,
                        MSG_LIST_COL_LEVEL, _(DEBUG_STR[debug_level]),
                        MSG_LIST_COL_MSG, message,
                        -1);

    g_free (str);


    switch (debug_level) {


    case SAT_LOG_LEVEL_BUG:
        bugs++;
        str = g_strdup_printf ("%d", bugs);
        gtk_label_set_text (GTK_LABEL (buglabel), str);
        g_free (str);
        break;


    case SAT_LOG_LEVEL_ERROR:
        errors++;
        str = g_strdup_printf ("%d", errors);
        gtk_label_set_text (GTK_LABEL (errlabel), str);
        g_free (str);
        break;


    case SAT_LOG_LEVEL_WARN:
        warnings++;
        str = g_strdup_printf ("%d", warnings);
        gtk_label_set_text (GTK_LABEL (warnlabel), str);
        g_free (str);
        break;


    case SAT_LOG_LEVEL_MSG:
        verboses++;
        str = g_strdup_printf ("%d", verboses);
        gtk_label_set_text (GTK_LABEL (verblabel), str);
        g_free (str);
        break;


    case SAT_LOG_LEVEL_DEBUG:
        traces++;
        str = g_strdup_printf ("%d", traces);
        gtk_label_set_text (GTK_LABEL (tracelabel), str);
        g_free (str);
        break;

    default:
        break;
    }


    total = bugs+errors+warnings+verboses+traces;
    str = g_strdup_printf ("<b>%d</b>", total);
    gtk_label_set_markup (GTK_LABEL (sumlabel), str);
    g_free (str);

}
