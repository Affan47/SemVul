my_locale_by_number(uint number)
{
  MY_LOCALE *locale;
  if (number >= array_elements(my_locales) - 1)
    return NULL;
  locale= my_locales[number];

  DBUG_ASSERT(locale == my_locales[locale->number]);
  return locale;
}
