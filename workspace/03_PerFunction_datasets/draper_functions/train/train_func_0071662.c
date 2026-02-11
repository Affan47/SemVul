cgi_free_form(formp)
     cgi_form *formp;
{
  if (formp)
    {
      if (formp->storage) free(formp->storage);
      if (formp->fields) free(formp->fields);
    }
  return;
}
