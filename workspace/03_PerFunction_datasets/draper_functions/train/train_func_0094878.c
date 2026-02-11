progcomp_insert (cmd, cs)
      char *cmd;
      COMPSPEC *cs;
{
  register BUCKET_CONTENTS *item;

  if (cs == NULL)
    programming_error (_("progcomp_insert: %s: NULL COMPSPEC"), cmd);

  if (prog_completes == 0)
    progcomp_create ();

  cs->refcount++;
  item = hash_insert (cmd, prog_completes, 0);
  if (item->data)
    free_progcomp (item->data);
  else
    item->key = savestring (cmd);
  item->data = cs;

  return 1;
}
