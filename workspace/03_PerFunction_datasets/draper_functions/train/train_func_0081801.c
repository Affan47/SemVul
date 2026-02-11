server_scan_error(struct server_scan *scan,
			      const char *message)
{
  output_window_append(ftc_client, message);
  log_normal("%s", message);

  switch (server_scan_get_type(scan)) {
  case SERVER_SCAN_LOCAL:
    server_scan_finish(pServer_scan);
    pServer_scan = NULL;
    pServer_list = NULL;
    break;
  case SERVER_SCAN_GLOBAL:
    server_scan_finish(pServer_scan);
    pServer_scan = NULL;
    pServer_list = NULL;
    break;
  case SERVER_SCAN_LAST:
    break;
  }
}
