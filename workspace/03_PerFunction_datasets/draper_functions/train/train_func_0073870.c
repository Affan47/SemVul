add_alias (char *name, char *alias)
{
  int i;


  i = find_alias_index (name);
  if (i >= 0)
    {
      free (alias_list[i].alias);
      alias_list[i].alias = xstrdup (alias);
    }
  else
    {
      if (alias_list_last >= alias_list_size)
        {
          alias_list_size *= 2;
          alias_list = xrealloc (alias_list, sizeof (alias_t) * alias_list_size);
        }

      alias_list[alias_list_last].name = xstrdup (name);
      alias_list[alias_list_last].alias = xstrdup (alias);
      alias_list_last++;
    }
}
