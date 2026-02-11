stv680_add_text (SANE_Byte * image, int width, int height, char *txt)
{
  SANE_Status status;
  time_t t;
  struct tm *tm;
  char line[MSG_MAXLEN + 1];
  SANE_Byte *ptr;
  int i, x, y, f, len;
  char fmtstring[25] = " %Y-%m-%d %H:%M:%S";
  char fmttxt[46];

  DBG (DBG_proc, "stv680_add_text: enter\n");
  time (&t);
  tm = localtime (&t);
  if (strlen (txt) > (MSG_MAXLEN - 23))
    strncpy (fmttxt, txt, (MSG_MAXLEN - 23));
  else
    strcpy (fmttxt, txt);
  strcat (fmttxt, fmtstring);

  len = strftime (line, MSG_MAXLEN, fmttxt, tm);

  for (y = 0; y < CHAR_HEIGHT; y++)
    {
      ptr = image + 3 * width * (height - CHAR_HEIGHT - 2 + y) + 12;

      for (x = 0; x < len; x++)
	{
	  f = fontdata[line[x] * CHAR_HEIGHT + y];
	  for (i = CHAR_WIDTH - 1; i >= 0; i--)
	    {
	      if (f & (CHAR_START << i))
		{
		  ptr[0] = 255;
		  ptr[1] = 255;
		  ptr[2] = 255;
		}
	      ptr += 3;
	    }
	}
    }

  DBG (DBG_proc, "stv680_add_text: exit vw=%d, vh=%d\n", width, height);
  status = (SANE_STATUS_GOOD);
  return status;

}
