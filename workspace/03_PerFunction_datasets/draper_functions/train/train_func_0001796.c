chise_ds_open_ccs_table (CHISE_DS *ds, const char *ccs)
{
  CHISE_CCS_Table* table;
  size_t len = strlen (ccs);

  if (ds == NULL)
    return NULL;

  table = (CHISE_CCS_Table*)malloc (sizeof (CHISE_CCS_Table));
  if (table == NULL)
    return NULL;

  table->ds = ds;
  table->db = NULL;
  table->access = 0;
  table->name = (unsigned char*)malloc (len + 1);
  if (table->name == NULL)
    {
      free (table);
      return NULL;
    }
  strcpy (table->name, ccs);
  return table;
}
