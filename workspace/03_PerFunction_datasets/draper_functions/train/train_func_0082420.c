get_raw_inktype(const stp_vars_t *v)
{
  if (strcmp(stp_get_string_parameter(v, "InputImageType"), "Raw") == 0)
    {
      const inklist_t *inks = stp_escp2_inklist(v);
      int ninktypes = inks->n_inks;
      int i;
      const char *channel_name = stp_get_string_parameter(v, "RawChannels");
      const channel_count_t *count;
      if (!channel_name)
	goto none;
      count = get_channel_count_by_name(channel_name);
      if (!count)
	goto none;
      for (i = 0; i < ninktypes; i++)
	if (inks->inknames[i].inkset == INKSET_EXTENDED &&
	    (inks->inknames[i].channel_count == count->count))
	  return &(inks->inknames[i]);
    }
 none:
  return get_inktype(v);
}
