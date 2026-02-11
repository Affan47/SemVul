__nl_langinfo_l (item, l)
     nl_item item;
     __locale_t l;
{
  int category = _NL_ITEM_CATEGORY (item);
  unsigned int index = _NL_ITEM_INDEX (item);
  const struct __locale_data *data;

  if (category < 0 || category == LC_ALL || category >= __LC_LAST)

    return (char *) "";


  if (index == _NL_ITEM_INDEX (_NL_LOCALE_NAME (category)))
    return (char *) l->__names[category];

  data = l->__locales[category];

  if (index >= data->nstrings)

    return (char *) "";


  return (char *) data->values[index].string;
}
