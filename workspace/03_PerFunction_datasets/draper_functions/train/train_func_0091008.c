vcount()
  {
    reset_error();
    std::string count_query;
    count_query+= "SELECT count(*) FROM ";
    count_query+= GEARMAN_QUEUE_SQLITE_DEFAULT_TABLE;

    int rows= 0;
    char *err= NULL;
    sqlite3_exec(_db, count_query.c_str(), sql_count, &rows, &err);

    if (err != NULL)
    {
      _error_string= err;
      sqlite3_free(err);
      return -1;
    }

    return rows;
  }
