replacechar(gchar *string, gchar find, gchar replace)
{


  gchar *tmp = string;

  if (!string || !find || !replace)
    return;

  while (*tmp)
    {
      if (*tmp == find)
	*tmp = replace;
      tmp ++;
    }
}
