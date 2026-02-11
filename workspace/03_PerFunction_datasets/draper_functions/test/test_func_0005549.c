_alloc_hdf (HDF **hdf, const char *name, size_t nlen,
                           const char *value, int dup, int wf, HDF *top)
{
  *hdf = calloc (1, sizeof (HDF));
  if (*hdf == NULL)
  {
    return nerr_raise (NERR_NOMEM, "Unable to allocate memory for hdf element");
  }

  (*hdf)->top = top;

  if (name != NULL)
  {
    (*hdf)->name_len = nlen;
    (*hdf)->name = (char *) malloc (nlen + 1);
    if ((*hdf)->name == NULL)
    {
      free((*hdf));
      (*hdf) = NULL;
      return nerr_raise (NERR_NOMEM,
	  "Unable to allocate memory for hdf element: %s", name);
    }
    strncpy((*hdf)->name, name, nlen);
    (*hdf)->name[nlen] = '\0';
  }
  if (value != NULL)
  {
    if (dup)
    {
      (*hdf)->alloc_value = 1;
      (*hdf)->value = strdup(value);
      if ((*hdf)->value == NULL)
      {
	free((*hdf)->name);
	free((*hdf));
	(*hdf) = NULL;
	return nerr_raise (NERR_NOMEM,
	    "Unable to allocate memory for hdf element %s", name);
      }
    }
    else
    {
      (*hdf)->alloc_value = wf;


      (*hdf)->value = (char *)value;
    }
  }
  return STATUS_OK;
}
