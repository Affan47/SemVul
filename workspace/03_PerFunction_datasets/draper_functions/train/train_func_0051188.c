th_set_group(TAR *t, gid_t gid)
{
#ifndef WIN32
  struct group *gr;

  gr = getgrgid(gid);
  if (gr != NULL)
    strlcpy(t->th_buf.gname, gr->gr_name, sizeof(t->th_buf.gname));
#endif
  int_to_oct(gid, t->th_buf.gid, 8);
}
