check_speed_level (th_enc_ctx * ctx, int *current, int *max)
{
  int ret;


  ret = th_encode_ctl (ctx, TH_ENCCTL_GET_SPLEVEL, current, sizeof (int));
  if (ret) {
    GST_WARNING ("Error %d getting current speed level.", ret);
    return ret;
  }

  ret = th_encode_ctl (ctx, TH_ENCCTL_GET_SPLEVEL_MAX, max, sizeof (int));
  if (ret) {
    GST_WARNING ("Error %d getting maximum speed level.", ret);
    return ret;
  }

  return 0;
}
