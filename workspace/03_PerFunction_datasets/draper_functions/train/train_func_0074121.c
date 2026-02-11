do_ssi_exec(struct mg_connection *conn, char *tag) {
  char cmd[IOBUF_SIZE];
  FILE *fp;

  if (sscanf(tag, " \"%[^\"]\"", cmd) != 1) {
    mg_printf(conn, "Bad SSI #exec: [%s]", tag);
  } else if ((fp = popen(cmd, "r")) == NULL) {
    mg_printf(conn, "Cannot SSI #exec: [%s]: %s", cmd, strerror(errno));
  } else {
    send_file_data(conn, fp);
    pclose(fp);
  }
}
