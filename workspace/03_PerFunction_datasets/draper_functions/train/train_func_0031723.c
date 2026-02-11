do_ssi_include(struct mg_connection *conn, const char *ssi,
                           char *tag, int include_level) {
  char file_name[IOBUF_SIZE], path[MAX_PATH_SIZE], *p;
  char **opts = (MG_CONN_2_CONN(conn))->server->config_options;
  FILE *fp;


  if (sscanf(tag, " virtual=\"%[^\"]\"", file_name) == 1) {

    mg_snprintf(path, sizeof(path), "%s%c%s",
                opts[DOCUMENT_ROOT], '/', file_name);
  } else if (sscanf(tag, " abspath=\"%[^\"]\"", file_name) == 1) {


    mg_snprintf(path, sizeof(path), "%s", file_name);
  } else if (sscanf(tag, " file=\"%[^\"]\"", file_name) == 1 ||
             sscanf(tag, " \"%[^\"]\"", file_name) == 1) {

    mg_snprintf(path, sizeof(path), "%s", ssi);
    if ((p = strrchr(path, '/')) != NULL) {
      p[1] = '\0';
    }
    mg_snprintf(path + strlen(path), sizeof(path) - strlen(path), "%s",
                file_name);
  } else {
    mg_printf(conn, "Bad SSI #include: [%s]", tag);
    return;
  }

  if ((fp = fopen(path, "rb")) == NULL) {
    mg_printf(conn, "Cannot open SSI #include: [%s]: fopen(%s): %s",
              tag, path, strerror(errno));
  } else {
    ns_set_close_on_exec(fileno(fp));
    if (mg_match_prefix(opts[SSI_PATTERN], strlen(opts[SSI_PATTERN]),
        path) > 0) {
      send_ssi_file(conn, path, fp, include_level + 1);
    } else {
      send_file_data(conn, fp);
    }
    fclose(fp);
  }
}
