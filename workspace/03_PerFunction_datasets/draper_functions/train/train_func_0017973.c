_setup_window2 (int argc, char **argv)
{
  intptr_t connect_to_remote_on_startup;

  gftp_lookup_request_option (window2.request, "connect_to_remote_on_startup",
                              &connect_to_remote_on_startup);

  if (argc == 2 && strncmp (argv[1], "--", 2) != 0)
    {
      if (gftp_parse_url (window2.request, argv[1]) == 0)
        ftp_connect (&window2, window2.request);
      else
        gftp_usage ();
    }
  else if (connect_to_remote_on_startup)
    {
      if (gftp_protocols[_get_selected_protocol ()].init (current_wdata->request) == 0)
        {
          gftp_setup_startup_directory (window2.request,
                                        "remote_startup_directory");
          gftp_connect (window2.request);
          ftp_list_files (&window2);
        }
    }
  else
    {


      sortrows (GTK_CLIST (window2.listbox), -1, &window2);
    }
}
