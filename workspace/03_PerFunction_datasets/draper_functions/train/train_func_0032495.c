send_directory_listing(struct connection *conn, const char *dir) {
  struct dir_entry *arr = NULL;
  int i, num_entries, sort_direction = conn->mg_conn.query_string != NULL &&
    conn->mg_conn.query_string[1] == 'd' ? 'a' : 'd';

  mg_send_header(&conn->mg_conn, "Transfer-Encoding", "chunked");
  mg_send_header(&conn->mg_conn, "Content-Type", "text/html; charset=utf-8");

  mg_printf_data(&conn->mg_conn,
              "<html><head><title>Index of %s</title>"
              "<style>th {text-align: left;}</style></head>"
              "<body><h1>Index of %s</h1><pre><table cellpadding=\"0\">"
              "<tr><th><a href=\"?n%c\">Name</a></th>"
              "<th><a href=\"?d%c\">Modified</a></th>"
              "<th><a href=\"?s%c\">Size</a></th></tr>"
              "<tr><td colspan=\"3\"><hr></td></tr>",
              conn->mg_conn.uri, conn->mg_conn.uri,
              sort_direction, sort_direction, sort_direction);

  num_entries = scan_directory(conn, dir, &arr);
  if (arr) {
      qsort(arr, num_entries, sizeof(arr[0]), compare_dir_entries);
      for (i = 0; i < num_entries; i++) {
        print_dir_entry(&arr[i]);
        NS_FREE(arr[i].file_name);
      }
      NS_FREE(arr);
  }

  write_terminating_chunk(conn);
  close_local_endpoint(conn);
}
