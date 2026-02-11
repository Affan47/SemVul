jd_who (u, str)
     JWHO u[];
     char *str;
{
  register int i;
  register int cnt;
  WNN_JWHO *jwho;

  JD_WNN_DEAD if ((cnt = js_who (jl_env (buf)->js_id, &ret_buf)) < 0)
    return (-1);
  jwho = (WNN_JWHO *) ret_buf.buf;
  for (i = 0; i < cnt; i++, jwho++)
    {
      u[i].sd = jwho[0].sd;
      u[i].user_name = str;
      strcpy (str, jwho->user_name);
      str += strlen (u[i].user_name) + 1;
      u[i].host_name = str;
      strcpy (str, jwho->host_name);
      str += strlen (u[i].host_name) + 1;
    }
  u[i].sd = -1;
  return (0);
}
