gl_locale_name_thread_unsafe (int category, const char *categoryname)
{
# if HAVE_USELOCALE
  {
    locale_t thread_locale = uselocale (NULL);
    if (thread_locale != LC_GLOBAL_LOCALE)
      {
#  if __GLIBC__ >= 2 && !defined __UCLIBC__


        const char *name =
          nl_langinfo (_NL_ITEM ((category), _NL_ITEM_INDEX (-1)));
        if (name[0] == '\0')


          name = thread_locale->__names[category];
        return name;
#  elif defined __FreeBSD__ || (defined __APPLE__ && defined __MACH__)

        int mask;

        switch (category)
          {
          case LC_CTYPE:
            mask = LC_CTYPE_MASK;
            break;
          case LC_NUMERIC:
            mask = LC_NUMERIC_MASK;
            break;
          case LC_TIME:
            mask = LC_TIME_MASK;
            break;
          case LC_COLLATE:
            mask = LC_COLLATE_MASK;
            break;
          case LC_MONETARY:
            mask = LC_MONETARY_MASK;
            break;
          case LC_MESSAGES:
            mask = LC_MESSAGES_MASK;
            break;
          default:
            return "";
          }
        return querylocale (mask, thread_locale);
#  endif
      }
  }
# endif
  return NULL;
}
