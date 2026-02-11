wire_display(int idx, char *key, char *from, char *message)
{
  char *enctmp;

  enctmp = decrypt_string(key, message);
  if (from[0] == '!')
    dprintf(idx, "----- > %s %s\n", &from[1], enctmp + 1);
  else
    dprintf(idx, "----- <%s> %s\n", from, enctmp);
  nfree(enctmp);
}
