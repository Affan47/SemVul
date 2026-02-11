netcgi2_apache_request_setup_client_block (value rv, value rp)
{
  CAMLparam2 (rv, rp);
  request_rec *r = Request_rec_val (rv);
  int i = ap_setup_client_block (r, Int_val (rp));
  CAMLreturn (Val_int(i));
}
