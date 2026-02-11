int_of_format(value format)
{
  int f = Int_val(format);

  if (!f--)
    return SND_PCM_FORMAT_S16_LE;
  else if (!f--)
    return SND_PCM_FORMAT_S24_3LE;
  else if (!f--)
    return SND_PCM_FORMAT_FLOAT;
  else if (!f--)
    return SND_PCM_FORMAT_FLOAT64;
  else
    assert(0);
}
