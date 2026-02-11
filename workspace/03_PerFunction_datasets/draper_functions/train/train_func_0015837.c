netcgi2_apache_request_method (value rv)
{
  CAMLparam1 (rv);
  request_rec *r = Request_rec_val (rv);
  CAMLreturn (copy_string (r->method));
}
