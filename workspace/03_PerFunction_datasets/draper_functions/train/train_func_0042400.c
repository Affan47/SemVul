append_alias (const void *nodep, VISIT value, int level)
{
  if (value != leaf && value != postorder)
    return;

  if (nalias_list_max == nalias_list)
    {
      nalias_list_max += 50;
      alias_list = (struct alias **) xrealloc (alias_list,
					       (nalias_list_max
						* sizeof (struct alias *)));
    }

  alias_list[nalias_list++] = *(struct alias **) nodep;
}
