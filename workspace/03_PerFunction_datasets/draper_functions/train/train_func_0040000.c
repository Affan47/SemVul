format5(struct ftio *ftio, struct options *opt)
{
#ifdef HAVE_PGSQL
  struct fts3rec_offsets fo;
  struct ftver ftv;
  char fields[1024], values[1024], query[3*1024];
  char *rec;
  char *db_host, *db_name, *db_table, *db_user, *db_pwd, *db_tmp, *tmp;
  char *db_port;
  int len;

  PGconn     *conn;
  PGresult   *res;

  db_host = DB_DEFAULT_DBHOST;
  db_name = DB_DEFAULT_DBNAME;
  db_port = DB_DEFAULT_DBPORT;
  db_user = DB_DEFAULT_DBUSER;
  db_table = DB_DEFAULT_DBTABLE;
  db_pwd = DB_DEFAULT_DBPWD;


  if (strlen(opt->dbaseURI)) {

    tmp = opt->dbaseURI;

    db_user = strsep(&tmp, ":");
    db_pwd = strsep(&tmp, ":");
    db_host = strsep(&tmp, ":");
    db_port = strsep(&tmp, ":");
    db_name = strsep(&tmp, ":");
    db_table = strsep(&tmp, ":");

    if (!db_user || !db_pwd || !db_host || !db_port || !db_name || !db_table) {
      fterr_warnx("Missing field in dbaseURI, expecting user:pwd:host:port:name:table.");
      return -1;
    }

  }

  ftio_get_ver(ftio, &ftv);

  fts3rec_compute_offsets(&fo, &ftv);


  opt->ft_mask &= ftrec_xfield(&ftv);


  fmt_xfields_type(fields, opt->ft_mask);


  conn = PQsetdbLogin(db_host, db_port, (char *) NULL, (char *) NULL, db_name, db_user, db_pwd);

  if (PQstatus(conn) == CONNECTION_BAD)
    fterr_errx(1,"PQsetdbLogin(): %s\n", PQerrorMessage(conn));


  while ((rec = ftio_read(ftio))) {

    len = fmt_xfields_val(values, rec, &fo, opt->ft_mask, 1);


    if (len) {
      strcpy (query, "INSERT INTO ");
      strcat (query, db_table);
      strcat (query, "(");
      strcat (query, fields);
      strcat (query, ") VALUES (");
      strcat (query, values);
      strcat (query, ")");

      if (debug)
        fprintf(stderr, "field=%s\n val=%s\n query=%s\n", fields, values,
          query);

      res = PQexec(conn, query);
      if (!res || PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        fterr_errx(1,"PQexec(): %s\n", PQerrorMessage(conn));
      }

    }

    ++opt->records;

  }


  PQfinish(conn);

#else

  fterr_warnx("Format not supported");

#endif

  return 0;

}
