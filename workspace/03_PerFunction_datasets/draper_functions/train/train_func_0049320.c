stab_int_type (void *p, unsigned int size, bfd_boolean unsignedp)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  long *cache;

  if (size <= 0 || (size > sizeof (long) && size != 8))
    {
      non_fatal (_("stab_int_type: bad size %u"), size);
      return FALSE;
    }

  if (unsignedp)
    cache = info->type_cache.signed_integer_types;
  else
    cache = info->type_cache.unsigned_integer_types;

  if (cache[size - 1] != 0)
    return stab_push_defined_type (info, cache[size - 1], size);
  else
    {
      long tindex;
      char buf[100];

      tindex = info->type_index;
      ++info->type_index;

      cache[size - 1] = tindex;

      sprintf (buf, "%ld=r%ld;", tindex, tindex);
      if (unsignedp)
	{
	  strcat (buf, "0;");
	  if (size < sizeof (long))
	    sprintf (buf + strlen (buf), "%ld;", ((long) 1 << (size * 8)) - 1);
	  else if (size == sizeof (long))
	    strcat (buf, "-1;");
	  else if (size == 8)
	    strcat (buf, "01777777777777777777777;");
	  else
	    abort ();
	}
      else
	{
	  if (size <= sizeof (long))
	    sprintf (buf + strlen (buf), "%ld;%ld;",
		     (long) - ((unsigned long) 1 << (size * 8 - 1)),
		     (long) (((unsigned long) 1 << (size * 8 - 1)) - 1));
	  else if (size == 8)
	    strcat (buf, "01000000000000000000000;0777777777777777777777;");
	  else
	    abort ();
	}

      return stab_push_string (info, buf, tindex, TRUE, size);
    }
}
