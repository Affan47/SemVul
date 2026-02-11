slot_proxy_handle_drop (GtkWidget                *widget,
			GdkDragContext           *context,
			unsigned int              time,
			NautilusDragSlotProxyInfo *drag_info)
{
  GtkWidget *window;
  NautilusWindowSlot *target_slot;
  NautilusView *target_view;
  char *target_uri;
  GList *uri_list;

  if (!drag_info->have_data ||
      !drag_info->have_valid_data) {
    gtk_drag_finish (context, FALSE, FALSE, time);
    drag_info_clear (drag_info);
    return;
  }

  window = gtk_widget_get_toplevel (widget);
  g_assert (NAUTILUS_IS_WINDOW (window));

  if (drag_info->target_slot != NULL) {
    target_slot = drag_info->target_slot;
  } else {
    target_slot = nautilus_window_get_active_slot (NAUTILUS_WINDOW (window));
  }

  target_uri = NULL;
  if (drag_info->target_file != NULL) {
    target_uri = nautilus_file_get_uri (drag_info->target_file);
  } else if (target_slot != NULL) {
    target_uri = nautilus_window_slot_get_current_uri (target_slot);
  }

  target_view = NULL;
  if (target_slot != NULL) {
    target_view = nautilus_window_slot_get_current_view (target_slot);
  }

  if (target_slot != NULL && target_view != NULL) {
    if (drag_info->info == NAUTILUS_ICON_DND_GNOME_ICON_LIST) {
      uri_list = nautilus_drag_uri_list_from_selection_list (drag_info->data.selection_list);
      g_assert (uri_list != NULL);

      nautilus_view_drop_proxy_received_uris (target_view,
                                              uri_list,
                                              target_uri,
                                              gdk_drag_context_get_selected_action (context));
      g_list_free_full (uri_list, g_free);
    } else if (drag_info->info == NAUTILUS_ICON_DND_URI_LIST) {
      nautilus_view_drop_proxy_received_uris (target_view,
                                              drag_info->data.uri_list,
                                              target_uri,
                                              gdk_drag_context_get_selected_action (context));
    } if (drag_info->info == NAUTILUS_ICON_DND_NETSCAPE_URL) {
      nautilus_view_handle_netscape_url_drop (target_view,
                                              drag_info->data.netscape_url,
                                              target_uri,
                                              gdk_drag_context_get_selected_action (context),
                                              0, 0);
    }


    gtk_drag_finish (context, TRUE, FALSE, time);
  } else {
    gtk_drag_finish (context, FALSE, FALSE, time);
  }

  g_free (target_uri);

  drag_info_clear (drag_info);
}
