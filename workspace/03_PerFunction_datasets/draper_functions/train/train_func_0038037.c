lisident (char **s)
{
  char            buffer[MAXIDLENGTH];
  int             r, nb = 0;

  for (nb = 0; (nb < MAXIDLENGTH) && isalnum (**s); nb++)
    buffer[nb] = *(*s)++;
  if (nb == MAXIDLENGTH)
     {
       fprintf (stderr, "Identificateur trop long!\n");
       return NULL;
     }
  buffer[nb] = 0;
  for (r = 0; r < numidents; r++)
    if (strcmp (idents[r].name, buffer) == 0)
       {
	 if (idents[r].symb == newvar)
	   idents[r].symb = oldvar;
	 return idents + r;
       }
  if (numidents == MAXIDENTS)
     {
       fprintf (stderr, "Too many different identifiers");
       return NULL;
     }
  idents[numidents].name = safedup (buffer);
  idents[numidents].symb = newvar;
  idents[numidents].table = NULL;
  return idents + numidents++;
}
