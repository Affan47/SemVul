send_index_page(struct mg_connection *conn) {
  const char *data;
  int data_len, ofs = 0;
  char var_name[100], file_name[100];

  mg_printf_data(conn, "%s",
                 "<html><body>Upload example."
                 "<form method=\"POST\" action=\"/handle_post_request\" "
                 "  enctype=\"multipart/form-data\">"
                 "<input type=\"file\" name=\"file1\" /> <br/>"
                 "<input type=\"file\" name=\"file2\" /> <br/>"
                 "<input type=\"submit\" value=\"Upload\" />"
                 "</form>");

  while ((ofs = mg_parse_multipart(conn->content + ofs, conn->content_len - ofs,
                                   var_name, sizeof(var_name),
                                   file_name, sizeof(file_name),
                                   &data, &data_len)) > 0) {
    mg_printf_data(conn, "var: %s, file_name: %s, size: %d bytes<br>",
                   var_name, file_name, data_len);
  }

  mg_printf_data(conn, "%s", "</body></html>");

  return MG_TRUE;
}
