qmail_put(qq,s,len) struct qmail *qq; char *s; int len;
{
  if (!qq->flagerr) if (substdio_put(&qq->ss,s,len) == -1) qq->flagerr = 1;
}
