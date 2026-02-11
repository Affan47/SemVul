explorer_get_current_tool(Explorer *self) {


    const ToolInfo *current = tool_table;

    for (current=tool_table; current->menu_name; current++) {
	GtkWidget *w = glade_xml_get_widget(self->xml, current->menu_name);
	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(w)))
	    return current;
    }
    return NULL;
}
