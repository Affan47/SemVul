auth_printsub (unsigned char *data, int cnt, char *buf, int buflen)
{
  TN_Authenticator *ap;

  ap = findauthenticator (data[1], data[2]);
  if (ap && ap->printsub)
    (*ap->printsub) (data, cnt, buf, buflen);
  else
    auth_gen_printsub (data, cnt, buf, buflen);
}
