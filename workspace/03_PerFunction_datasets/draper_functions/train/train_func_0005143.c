tree_view_mouse_click(GdkEventButton* event_p,
					void* data) {
    if (event_p->type == GDK_2BUTTON_PRESS) {
      SocketListDialog* instance_p = static_cast<SocketListDialog*>(data);
      int x, y;
      gtk_widget_get_pointer(GTK_WIDGET(instance_p->tree_view_p), &x, &y);
      if (x >= 0 && y >= 0
	  && gtk_tree_view_get_dest_row_at_pos(instance_p->tree_view_p,
					       x, y, 0, 0)) {
	instance_p->view_file();
      }
    }
    return false;
  }
}
