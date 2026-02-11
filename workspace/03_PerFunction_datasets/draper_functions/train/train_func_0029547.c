pamd_set_location(char *ln, char *rh)
{
  line = strdup(ln);
  rhost = strdup(rh?rh:"localhost");
}
