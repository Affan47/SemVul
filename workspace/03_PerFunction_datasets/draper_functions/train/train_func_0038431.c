initring (void)
{
  int i;

  endring = ring;

  for (i = 0; i <= 128; ++i)
    if (isprint (i))
      *endring++ = i;
}
