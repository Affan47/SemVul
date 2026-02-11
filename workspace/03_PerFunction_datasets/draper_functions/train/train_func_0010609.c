connectdlg_serverlist_update_callback(Widget w, XtPointer client_data,
                                           XtPointer call_data)
{
  if (lan_mode) {
    if (!lan_scan) {
      lan_scan = server_scan_begin(SERVER_SCAN_LOCAL, server_scan_error);
    }
    if (num_lanservers_timer == 0) {
      server_list_timer(connectdlg_serverlist_list, NULL);
    }
  } else {
    if (!meta_scan) {
      meta_scan = server_scan_begin(SERVER_SCAN_GLOBAL, server_scan_error);
    }
    if (num_lanservers_timer == 0) {
      server_list_timer(connectdlg_serverlist_list, NULL);
    }
  }
}
