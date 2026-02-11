serbb_highpulsepin(PROGRAMMER * pgm, int pin)
{
  if ( (pin & PIN_MASK) < 1 || (pin & PIN_MASK) > DB9PINS )
    return -1;

  serbb_setpin(pgm, pin, 1);
  serbb_setpin(pgm, pin, 0);

  return 0;
}
