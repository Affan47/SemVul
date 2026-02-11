default_button_create_value(char *title, GtkWidget *hbox,
                            GapArrArg *arr_ptr, t_arr_interface *arrint_ptr,
                            t_all_arr_args *arr_all)
{
    GtkWidget *button;

    button = gtk_button_new_from_stock (GIMP_STOCK_RESET);
    g_object_set_data (G_OBJECT (button), GAP_ARR_INTERFACE_PTR, (gpointer)arrint_ptr);

    gtk_widget_show(button);
    g_signal_connect (G_OBJECT (button), "clicked",
                      G_CALLBACK(default_button_cb),
                      arr_all);

    gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);


    if(arr_ptr->help_txt != NULL)
    {
       gimp_help_set_help_data(button, arr_ptr->help_txt,NULL);
    }
}
