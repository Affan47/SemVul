cselib_record_autoinc_cb (rtx mem ATTRIBUTE_UNUSED, rtx op ATTRIBUTE_UNUSED,
			  rtx dest, rtx src, rtx srcoff, void *arg)
{
  struct cselib_record_autoinc_data *data;
  data = (struct cselib_record_autoinc_data *)arg;

  data->sets[data->n_sets].dest = dest;

  if (srcoff)
    data->sets[data->n_sets].src = gen_rtx_PLUS (GET_MODE (src), src, srcoff);
  else
    data->sets[data->n_sets].src = src;

  data->n_sets++;

  return -1;
}
