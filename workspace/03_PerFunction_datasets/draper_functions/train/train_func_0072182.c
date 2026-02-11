send_response(HTTPExchange * exchange, uint16_t status_code, const char * html) {
  HTTPExchange_set_status_code(exchange, status_code);
  if (HTTPExchange_write_response(exchange, html, strlen(html)) != 0) {
    HTTPServer_log_err("Warning: error writing to client\n");
  }
}
