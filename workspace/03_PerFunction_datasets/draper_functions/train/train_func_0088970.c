stp_channel_convert(const stp_vars_t *v, unsigned *zero_mask)
{
  if (input_has_special_channels(v))
    generate_special_channels(v);
  else if (output_has_gloss(v) && !input_needs_splitting(v))
    copy_channels(v);
  if (output_needs_gcr(v))
    do_gcr(v);
  if (input_needs_splitting(v))
    split_channels(v, zero_mask);
  else
    scale_channels(v, zero_mask);
  (void) limit_ink(v);
  (void) generate_gloss(v, zero_mask);
}
