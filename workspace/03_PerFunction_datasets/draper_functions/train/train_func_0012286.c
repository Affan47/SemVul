ff_gulp_parse(const gchar *text)
{
gint i;
gchar **line;
gpointer test;
GSList *list=NULL;
struct forcefield_pak *ff=NULL;

#if DEBUG_FF_GULP_PARSE
printf("---------------\n");
printf("%s", text);
printf("---------------\n");
#endif


if (!text)
  return(NULL);
line = g_strsplit(text, "\n", -1);
if (!line)
  return(NULL);


i=0;
while (*(line+i))
  {

  test = ff_gulp_new(*(line+i));
  if (test)
    {

    ff = test;
    list = g_slist_prepend(list, ff);
    }
  else
    {

    if (ff)
      ff_data_add(ff, *(line+i));
    }
  i++;
  }

g_strfreev(line);

list = g_slist_reverse(list);

#if DEBUG_FF_GULP_PARSE
ff_dump_all(list);
#endif

return(list);
}
