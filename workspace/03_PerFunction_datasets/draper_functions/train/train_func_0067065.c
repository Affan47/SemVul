idle_cb_update_test_case_row (gpointer data)
{
    TestCaseRowInfo *info = data;
    CutGtkUI *ui;
    GtkTreeIter iter;

    ui = info->ui;

    if (gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(ui->logs),
                                            &iter, info->path)) {
        gdouble fraction;
        gint percent;
        gchar *text;
        GdkPixbuf *icon;

        fraction = info->n_completed_tests / (gdouble)info->n_tests;
        percent = (gint)(fraction * 100);
        text = g_strdup_printf("%d/%d (%d%%)",
                               info->n_completed_tests, info->n_tests, percent);
        icon = get_status_icon(ui->tree_view, info->status);
        gtk_tree_store_set(ui->logs, &iter,
                           COLUMN_PROGRESS_TEXT, text,
                           COLUMN_PROGRESS_VALUE, percent,
                           COLUMN_STATUS_ICON, icon,
                           COLUMN_COLOR, status_to_color(info->status, TRUE),
                           -1);
        g_free(text);
        g_object_unref(icon);
    }

    return FALSE;
}
