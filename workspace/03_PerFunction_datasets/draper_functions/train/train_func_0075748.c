_soap_admin_list_routers(httpd_conn_t *conn)
{
  SoapRouterNode *node;
  char buffer[1024];

  _soap_admin_send_title(conn, "Available routers");

  http_output_stream_write_string(conn->out, "<ul>");
  for (node = soap_server_get_routers(); node; node = node->next)
  {
    sprintf(buffer, "<li><a href=\"?" SOAP_ADMIN_QUERY_ROUTER "=%s\">%s</a> - <a href=\"%s\">[Service Description]</a></li>",
	    node->context, node->context, node->context);
    http_output_stream_write_string(conn->out, buffer);
  }
  http_output_stream_write_string(conn->out, "</ul>");

  http_output_stream_write_string(conn->out, "</body></html>");
}
