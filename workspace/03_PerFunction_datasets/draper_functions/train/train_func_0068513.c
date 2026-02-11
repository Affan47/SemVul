authenticate_basic_user(request_rec *r)
{
  int res;
  const char *sent_pw;


  res = ap_get_basic_auth_pw(r, &sent_pw);
  if (res != OK)
    return res;

  return authenticate_basic_user_common(r, r->user, sent_pw);
}
