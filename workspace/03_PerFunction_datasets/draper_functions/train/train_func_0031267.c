set_gray_transition_parameter(const stp_vars_t *v,
			      stp_parameter_t *description,
			      int expected_channels)
{
  const inkname_t *ink_name = get_inktype_only(v);
  description->is_active = 0;
  if (!ink_name &&
      ((expected_channels == 4 && printer_supports_inkset(v, INKSET_QUADTONE)) ||
       (expected_channels == 6 && printer_supports_inkset(v, INKSET_HEXTONE))))
    fill_transition_parameters(v, description, STP_ECOLOR_K);
  if (ink_name &&
      (ink_name->channels[STP_ECOLOR_K].n_subchannels ==
       expected_channels))
    fill_transition_parameters(v, description, STP_ECOLOR_K);
  else
    set_color_transition_parameter(v, description, STP_ECOLOR_K);
}
