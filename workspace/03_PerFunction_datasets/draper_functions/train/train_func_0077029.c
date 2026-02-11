expire(time_t t) {
  DBT key; memset(&key, 0, sizeof(DBT));
  DBT data; memset(&data, 0, sizeof(DBT));
  AutoCursor cursor;

  if (db->cursor(db, 0, &cursor.c, 0) != 0) return;

  int status;
  while ((status = cursor.get(&key, &data, DB_NEXT)) == 0) {
    time_t lastAccess = 0;

    if (data.data != 0)
      unserialize4(lastAccess, static_cast<byte*>(data.data) + ACCESS);

    if (static_cast<signed>(t - lastAccess) > 0) {
      debug("Cache: expiring %1",
            string(static_cast<char*>(key.data), key.size));
      cursor.del(0);
    }
  }
  if (status != DB_NOTFOUND)
    throw DbError(status);
}
