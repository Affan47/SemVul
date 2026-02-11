server_list_timer(XtPointer meta_list, XtIntervalId * id)
{
  char errbuf[128];

  if (!connectdlg_serverlist_shell) {
    return;
  }

  if (get_server_list(servers_list, errbuf, sizeof(errbuf)) != -1)  {
    XawListChange(meta_list, servers_list, 0, 0, True);
  }


  num_lanservers_timer++;

  if (lan_mode) {
    if (num_lanservers_timer == 20) {
      server_scan_finish(lan_scan);
      lan_scan = NULL;
      num_lanservers_timer = 0;
      return;
    }
    (void)XtAppAddTimeOut(app_context, 250, server_list_timer,
                          (XtPointer)meta_list);
  } else {
    if (num_lanservers_timer == 4) {
      server_scan_finish(meta_scan);
      meta_scan = NULL;
      num_lanservers_timer = 0;
      return;
    }
    (void)XtAppAddTimeOut(app_context, 500, server_list_timer,
                          (XtPointer)meta_list);
  }
}
