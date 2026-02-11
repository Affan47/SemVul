__create_ib_request (const_nis_name name, unsigned int flags)
{
  struct ib_request *ibreq = calloc (1, sizeof (struct ib_request));
  nis_attr *search_val = NULL;
  size_t search_len = 0;
  size_t size = 0;

  if (ibreq == NULL)
    return NULL;

  ibreq->ibr_flags = flags;

  char *cptr = strdupa (name);


  if (cptr[0] != '[')
    {
      ibreq->ibr_name = strdup (cptr);
      if (ibreq->ibr_name == NULL)
	{
	  free (ibreq);
	  return NULL;
	}
      return ibreq;
    }


  ibreq->ibr_name = strchr (cptr, ']');
  if (ibreq->ibr_name == NULL || ibreq->ibr_name[1] != ',')
    {

      free (ibreq);
      return NULL;
    }


  if (ibreq->ibr_name[-1] == ',')
    ibreq->ibr_name[-1] = '\0';
  else
    ibreq->ibr_name[0] = '\0';
  ibreq->ibr_name += 2;
  ibreq->ibr_name = strdup (ibreq->ibr_name);
  if (ibreq->ibr_name == NULL)
    {
    free_null:
      while (search_len-- > 0)
	{
	  free (search_val[search_len].zattr_ndx);
	  free (search_val[search_len].zattr_val.zattr_val_val);
	}
      free (search_val);
      nis_free_request (ibreq);
      return NULL;
    }

  ++cptr;

  while (cptr != NULL && cptr[0] != '\0')
    {
      char *key = cptr;
      char *val = strchr (cptr, '=');

      cptr = strchr (key, ',');
      if (cptr != NULL)
	*cptr++ = '\0';

      if (__builtin_expect (val == NULL, 0))
	{
	  nis_free_request (ibreq);
	  return NULL;
	}
      *val++ = '\0';
      if (search_len + 1 >= size)
	{
	  size += 1;
	  nis_attr *newp = realloc (search_val, size * sizeof (nis_attr));
	  if (newp == NULL)
	    goto free_null;
	  search_val = newp;
	}
      search_val[search_len].zattr_ndx = strdup (key);
      if (search_val[search_len].zattr_ndx == NULL)
	goto free_null;

      search_val[search_len].zattr_val.zattr_val_len = strlen (val) + 1;
      search_val[search_len].zattr_val.zattr_val_val = strdup (val);
      if (search_val[search_len].zattr_val.zattr_val_val == NULL)
	{
	  free (search_val[search_len].zattr_ndx);
	  goto free_null;
	}

      ++search_len;
    }

  ibreq->ibr_srch.ibr_srch_val = search_val;
  ibreq->ibr_srch.ibr_srch_len = search_len;

  return ibreq;
}
