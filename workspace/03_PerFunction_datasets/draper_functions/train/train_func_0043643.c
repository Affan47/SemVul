alloc_adm_entry (int fields)
{
  AdmEntry *res = (AdmEntry *) xmalloc (sizeof (AdmEntry));
  int x;

  res->fieldcount = fields;
  res->admFields = (char **) xmalloc (sizeof (char *) * fields);
  res->next = NULL;
  for (x = 0; x < fields; x++)
    {
      res->admFields[x] = NULL;
    }
  return res;
}
