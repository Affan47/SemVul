chise_feature_sync (CHISE_Feature feature)
{
  int status;

  if (feature->db == NULL)
    status = 0;
  else
    status = CHISE_Attribute_Table_close (feature->db);
  feature->db = NULL;
  feature->access = 0;
  return status;
}
