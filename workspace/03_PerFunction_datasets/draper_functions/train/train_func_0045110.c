gwy_sci_text_button_some_pressed(GwySciText *sci_text,
                                 GtkWidget *button)
{
    GtkEditable *editable;
    gboolean selected;
    gint i, start, end;
    gsize j;

    i = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "type"));
    editable = GTK_EDITABLE(sci_text->entry);
    selected = gtk_editable_get_selection_bounds(editable, &start, &end);
    if (!selected) {
        start = gtk_editable_get_position(editable);
        end = start;
    }
    for (j = 0; j < G_N_ELEMENTS(tags); j++) {
        if (tags[j].tag == i) {
            gtk_editable_insert_text(editable,
                                     tags[j].start, tags[j].len, &start);
            end += tags[j].len;
            gtk_editable_insert_text(editable,
                                     tags[j].end, tags[j].len+1, &end);
            gtk_widget_grab_focus(GTK_WIDGET(sci_text->entry));
            if (selected)
                gtk_editable_select_region(editable, start, end-tags[j].len-1);
            else
                gtk_editable_set_position(editable, start);
            break;
        }
    }
}
