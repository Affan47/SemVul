netcgi2_apache_table_get_all(value tv, value str)
{
  CAMLparam2(tv, str);
  CAMLlocal1(res);
  table *t = Table_val(tv);
  char *key = String_val(str);
  res = Val_int(0);


  apr_table_do(&netcgi2_apache_table_get_loop, &res, t, key, NULL);
  CAMLreturn(res);
}
