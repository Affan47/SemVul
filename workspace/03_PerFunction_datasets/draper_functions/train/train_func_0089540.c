drop_unused_digis(struct ax_calls *calls)
{
  if (!calls->ax_n_digis || calls->ax_next_digi >= calls->ax_n_digis)
    return;
  if ((calls->ax_n_digis = calls->ax_next_digi) > 0) {
    calls->ax_digi_call[calls->ax_next_digi-1].ax25_call[ALEN] |= HDLCAEB;
  } else {
    calls->ax_from_call.ax25_call[ALEN] |= HDLCAEB;
  }
  if (Verbose)
    fprintf(stderr,"3rd party: Unused digis have been dropped.\n");
}
