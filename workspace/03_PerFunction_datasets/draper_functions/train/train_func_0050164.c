strextname(char *pathname)
{
  char *dot, *slash;

  dot = strrchr(pathname, (int) '.');
  slash = strrchr(pathname, (int) '/');

  if (dot != NULL) {
	if (slash == NULL || slash < dot)
	  return(strdup(dot));
  }

  return(NULL);
}
