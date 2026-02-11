tty_tspeed (int val)
{
#ifdef	DECODE_BAUD
  struct termspeeds *tp;

  for (tp = termspeeds; (tp->speed != -1) && (val > tp->speed); tp++)
    ;
  if (tp->speed == -1)
    --tp;
  val = tp->value;
#endif
  cfsetospeed (&termbuf, val);
}
