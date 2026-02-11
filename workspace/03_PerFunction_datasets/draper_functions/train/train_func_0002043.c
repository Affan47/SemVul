se_prop_read_xine_id_string (const se_prop_t *prop, se_prop_read_t *value)
{
  xine_cfg_entry_t entry;
  if (xine_config_lookup_entry (xine, (const char *) prop->data, &entry))
    value->s = entry.str_value;
  else
    value->s = "";
}
