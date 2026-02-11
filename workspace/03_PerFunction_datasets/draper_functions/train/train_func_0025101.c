chise_feature_set_property_value (CHISE_Feature feature,
				  CHISE_Property property,
				  unsigned char *value)
{
  if (property == NULL)
    return -1;
  if (chise_property_setup_db (property, 1))
    return -1;
  return chise_attribute_table_put (property->db, feature->name, value);
}
