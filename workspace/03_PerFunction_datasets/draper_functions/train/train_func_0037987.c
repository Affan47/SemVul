af_unregtmpfile (name)
     char *name;
{
  register int i;
  for (i=0; i < OPEN_MAX; i++)
    if (tmpfilelist[i] == name) {
      tmpfilelist[i] = NULL;
      break;
    }
  if (i == OPEN_MAX)
    af_wng ("unregtmpfile", "name of tmpfile has not been registered before");
}
