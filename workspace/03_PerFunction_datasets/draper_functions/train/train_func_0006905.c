gsb_form_widget_free_list ( void )
{
    GSList *tmp_list;

    devel_debug (NULL);

    if (!form_list_widgets)
        return FALSE;

    tmp_list = form_list_widgets;
    while (tmp_list)
    {
        struct_element *element;

        element = tmp_list -> data;

        if (! element )
            continue;


        if ( element -> element_widget )
        {
            if (GTK_IS_WIDGET (element -> element_widget))
            {


                if (GTK_IS_COMBOFIX (element -> element_widget))
                {
                    g_signal_handlers_block_by_func ( element -> element_widget,
                        gsb_payment_method_changed_callback, NULL );
                    gtk_combofix_set_text ( GTK_COMBOFIX (element -> element_widget), "" );
                    gsb_form_widget_set_empty ( GTK_WIDGET ( element -> element_widget ), TRUE );
                }
                gtk_widget_destroy (element -> element_widget);
                element -> element_widget = NULL;
            }
        }
        else
        {
            alert_debug ("element_widget is NULL\n");
        }
        g_free (element);
        tmp_list = tmp_list -> next;
    }
    g_slist_free (form_list_widgets);
    form_list_widgets = NULL;

    return FALSE;
}
