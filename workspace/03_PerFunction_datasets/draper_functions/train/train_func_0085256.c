sorttab_display_new(GtkPaned *sort_tab_parent, gchar *glade_path) {
    g_return_if_fail(sort_tab_parent);
    g_return_if_fail(glade_path);

    gint sort_tab_total = sort_tab_widget_get_max_index();

    gint inst;
    GtkPaned *parent;
    GList *paneds = NULL;

    for (gint i = 0; i < sort_tab_total; ++i) {
        if (i == 0)
            parent = sort_tab_parent;
        else
            parent = _st_create_paned(parent);

        paneds = g_list_append(paneds, parent);
    }


    SortTabWidget *next = NULL;
    for (inst = sort_tab_total; inst >= 0; --inst) {
        if (inst == sort_tab_total)
            parent = g_list_nth_data(paneds, inst - 1);
        else
            parent = g_list_nth_data(paneds, inst);

        first_sort_tab_widget = sort_tab_widget_new(inst, GTK_WIDGET(parent), glade_path);

        sort_tab_widget_set_next(first_sort_tab_widget, next);
        if (next)
            sort_tab_widget_set_previous(next, first_sort_tab_widget);

        next = first_sort_tab_widget;


        if (inst == sort_tab_total) {
            gtk_paned_pack2(parent, GTK_WIDGET(first_sort_tab_widget), TRUE, TRUE);
        }
        else {
            gtk_paned_pack1(parent, GTK_WIDGET(first_sort_tab_widget), FALSE, TRUE);
        }
    }
    next = NULL;
}
