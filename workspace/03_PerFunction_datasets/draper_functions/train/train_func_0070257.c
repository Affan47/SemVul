info_apropos (char *string)
{
  REFERENCE **apropos_list;

  apropos_list = apropos_in_all_indices (string, 0);

  if (!apropos_list)
    info_error (_(APROPOS_NONE), string);
  else
    {
      register int i;
      REFERENCE *entry;

      for (i = 0; (entry = apropos_list[i]); i++)
        fprintf (stdout, "\"(%s)%s\" -- %s\n",
                 entry->filename, entry->nodename, entry->label);
    }
  info_free_references (apropos_list);
}
