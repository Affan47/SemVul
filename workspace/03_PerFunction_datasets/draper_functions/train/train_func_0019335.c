ui_combo_get_current_data(GtkCombo *combo)
{
    GtkList *listw = GTK_LIST(combo->list);

    if (listw->selection == 0)
    	return 0;
    return gtk_object_get_data(GTK_OBJECT(listw->selection->data),
    	    	    	       ui_combo_item_key);
}
