db_key_type (DB *db, u_int32_t action) {
  switch (db_get_type(db)) {
    case DB_QUEUE: case DB_RECNO: return -1;
    case DB_BTREE: switch (action) {
      case DB_GET_RECNO: case DB_SET_RECNO: return -1;
      default: return 0;
    }
    default: return 0;
  }
}
