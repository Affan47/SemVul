gap_timeconv_samples_to_frames( gint32 samples, gdouble samplerate, gdouble framerate)
{
  gdouble  secs;
  gdouble  frames;

  if((samplerate < 1) || (framerate < 1))
  {
    return (0);
  }

  secs = (gdouble)samples / samplerate;
  frames = secs * framerate;

  return(frames);
}
