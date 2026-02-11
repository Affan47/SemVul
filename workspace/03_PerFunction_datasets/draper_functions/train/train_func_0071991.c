play_sound (k)
     int             k;
{
  char            c;
  test_sound ();
  c = k;
  if ((playSounds) && (audioOK))
    write (soundfd, &c, sizeof (c));
  return 0;
}
