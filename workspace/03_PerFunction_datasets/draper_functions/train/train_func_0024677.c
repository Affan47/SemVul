__duplocale (__locale_t dataset)
{

  if (dataset == _nl_C_locobj_ptr)
    return dataset;


  if (dataset == LC_GLOBAL_LOCALE)
    dataset = &_nl_global_locale;

  __locale_t result;
  int cnt;
  size_t names_len = 0;


  for (cnt = 0; cnt < __LC_LAST; ++cnt)
    if (cnt != LC_ALL && dataset->__names[cnt] != _nl_C_name)
      names_len += strlen (dataset->__names[cnt]) + 1;


  result = malloc (sizeof (struct __locale_struct) + names_len);

  if (result != NULL)
    {
      char *namep = (char *) (result + 1);


      __libc_rwlock_wrlock (__libc_setlocale_lock);

      for (cnt = 0; cnt < __LC_LAST; ++cnt)
	if (cnt != LC_ALL)
	  {
	    result->__locales[cnt] = dataset->__locales[cnt];
	    if (result->__locales[cnt]->usage_count < MAX_USAGE_COUNT)
	      ++result->__locales[cnt]->usage_count;

	    if (dataset->__names[cnt] == _nl_C_name)
	      result->__names[cnt] = _nl_C_name;
	    else
	      {
		result->__names[cnt] = namep;
		namep = __stpcpy (namep, dataset->__names[cnt]) + 1;
	      }
	  }


      result->__ctype_b = dataset->__ctype_b;
      result->__ctype_tolower = dataset->__ctype_tolower;
      result->__ctype_toupper = dataset->__ctype_toupper;


      __libc_rwlock_unlock (__libc_setlocale_lock);
    }

  return result;
}
