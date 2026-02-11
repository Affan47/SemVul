vrc7_process (void)
{
  static int sample = 0;


  if (sample >= buflen) {
    sample -= buflen;
    YM3812UpdateOne (vrc7.ym3812, buffer, buflen);
  }

  return (int32) ((int16 *) buffer)[sample++];
}
