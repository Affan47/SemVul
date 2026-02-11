do_revision(uschar *p)
{
if (revision != NULL)
  {
  free(revision);
  revision = NULL;
  }

if (*p != 0 && Ustrcmp(p, "off") != 0)
  {
  revision = misc_malloc(Ustrlen(p) + 1);
  Ustrcpy(revision, p);
  }
}
