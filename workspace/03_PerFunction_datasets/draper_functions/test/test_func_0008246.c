DrawBlackMaskedText (int xp, int yp, char *text)
{
  if (!shm)
    {
      XDrawString (dp, current.pixmap, blackgc, xp, yp + 7, text, strlen (text));
    }
  else
    {
      SetWriteMode (WRITEMODE_MASKED);
      SetFont (8, 8, fontblack);
      FWrite (xp, yp, text);

    }
}
