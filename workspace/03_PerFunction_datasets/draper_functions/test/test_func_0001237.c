process_print (void)
{
  if ( is_onset ) {
    outmsg ("%f\n", aubio_onset_get_last_s (o) );
  }
}
