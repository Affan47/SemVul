on_combobox_starting_map_changed(GtkComboBox *box, gpointer user_data)
{
    int active_entry, i;
    GtkWidget **label_stat;
    Race_Class_Info *rc;
    char buf[256];

    active_entry = gtk_combo_box_get_active(box);


    if (active_entry == -1)
        return;


    gtk_text_buffer_set_text(textbuf_starting_map, "", 0);
    add_marked_text_to_pane(&create_char_pane[STARTING_MAP_PANE],
                            starting_map_info[active_entry].description, 0, 0, 0);

}
