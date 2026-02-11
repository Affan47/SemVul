transcmp (p1, p2)
     const void *p1;
     const void *p2;
{
  const struct known_translation_t *s1;
  const struct known_translation_t *s2;
  int result;

  s1 = (const struct known_translation_t *) p1;
  s2 = (const struct known_translation_t *) p2;

  result = strcmp (s1->domain != NULL ? s1->msgid.appended : s1->msgid.ptr,
		   s2->domain != NULL ? s2->msgid.appended : s2->msgid.ptr);
  if (result == 0)
    {
      result = strcmp (s1->domainname, s2->domainname);
      if (result == 0)
	{
#ifdef HAVE_PER_THREAD_LOCALE
	  result = strcmp (s1->localename, s2->localename);
	  if (result == 0)
#endif


	    result = s1->category - s2->category;
	}
    }

  return result;
}
