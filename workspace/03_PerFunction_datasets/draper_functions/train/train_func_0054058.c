create_children (GNCGeneralSearch *gsl,
                 const char       *label,
                 gboolean          text_editable,
                 QofIdTypeConst    type,
                 QofBook          *book)
{
    GtkListStore *	list_store;
    QofQuery *	q;
    GtkTreeIter iter;
    GList * list, * it;
    GtkEntryCompletion *completion;


    gsl->entry = gtk_entry_new ();
    if (!text_editable)
        gtk_editable_set_editable (GTK_EDITABLE (gsl->entry), FALSE);
    gtk_box_pack_start (GTK_BOX (gsl), gsl->entry, TRUE, TRUE, 0);


    q = qof_query_create_for (type);
    qof_query_add_boolean_match(q, g_slist_prepend
                                (NULL, QOF_PARAM_ACTIVE), TRUE, QOF_QUERY_AND);
    qof_query_set_book (q, book);
    list = qof_query_run(q);


    list_store = gtk_list_store_new (GSL_N_COLUMNS, G_TYPE_STRING, G_TYPE_OBJECT);
    for (it = list; it != NULL ; it = it->next)
    {
        char * name;

        name = g_strdup(qof_object_printable(type, it->data));

        if (name)
        {
            gtk_list_store_append (list_store, &iter);
            gtk_list_store_set (list_store, &iter,
                                GSL_COLUMN_TEXT, name,
                                GSL_COLUMN_QOFOBJECT, G_OBJECT(it->data),
                                -1);
            g_free(name);
        }

    }

    qof_query_destroy(q);


    completion = gtk_entry_completion_new();
    gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(list_store));
    gtk_entry_completion_set_text_column(completion, 0);
    gtk_entry_completion_set_inline_completion(completion, TRUE);
    gtk_entry_set_completion(GTK_ENTRY(gsl->entry), completion);

    g_signal_connect (G_OBJECT (completion), "match_selected",
                      G_CALLBACK (gnc_gsl_match_selected_cb), gsl);
    g_signal_connect (G_OBJECT (gsl->entry), "focus-out-event",
                      G_CALLBACK (gnc_gsl_focus_out_cb), gsl);

    g_object_unref(completion);
    gtk_widget_show (gsl->entry);


    gsl->button = gtk_button_new_with_label (label);
    gtk_box_pack_start (GTK_BOX (gsl), gsl->button, FALSE, FALSE, 0);
    g_signal_connect (G_OBJECT (gsl->button), "clicked",
                      G_CALLBACK (search_cb), gsl);
    gtk_widget_show (gsl->button);
}
