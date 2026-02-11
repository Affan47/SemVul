sysgethostname()
{
  A	r;
  char	name[MAXHOSTNAMELEN];
  r = (gethostname(name, MAXHOSTNAMELEN)) ? (A)gz() : (A)gsv(0, name);
  R r;
}
