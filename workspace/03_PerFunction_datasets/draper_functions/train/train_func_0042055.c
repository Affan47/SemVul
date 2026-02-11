cson_sqlite3_column_to_value( sqlite3_stmt * st, int col )
{
    if( ! st ) return NULL;
    else
    {
#if 0
        sqlite3_value * val = sqlite3_column_type(st,col);
        int const vtype = val ? sqlite3_value_type(val) : -1;
        if( ! val ) return cson_value_null();
#else
        int const vtype = sqlite3_column_type(st,col);
#endif
        switch( vtype )
        {
          case SQLITE_NULL:
              return cson_value_null();
          case SQLITE_INTEGER:

              return cson_value_new_integer( (cson_int_t) sqlite3_column_int64(st, col)  );
          case SQLITE_FLOAT:
              return cson_value_new_double( sqlite3_column_double(st, col) );
          case SQLITE_BLOB:
          case SQLITE_TEXT: {
              char const * str = (char const *)sqlite3_column_text(st,col);
              return cson_value_new_string(str, str ? strlen(str) : 0);
          }
          default:
              return NULL;
        }
    }
}
