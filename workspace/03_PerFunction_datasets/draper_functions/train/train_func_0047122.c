free_category (int category,
	       struct __locale_data *here, struct __locale_data *c_data)
{
  struct loaded_l10nfile *runp = _nl_locale_file_list[category];


  if (here != c_data)
    {


      setdata (category, c_data);
      setname (category, _nl_C_name);
    }

  while (runp != NULL)
    {
      struct loaded_l10nfile *curr = runp;
      struct __locale_data *data = (struct __locale_data *) runp->data;

      if (data != NULL && data != c_data)
	_nl_unload_locale (data);
      runp = runp->next;
      free ((char *) curr->filename);
      free (curr);
    }
}
