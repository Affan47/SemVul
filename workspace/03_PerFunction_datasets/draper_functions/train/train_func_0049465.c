digraph(Yshort **relation)
{
  register int i;

  infinity = ngotos + 2;
  INDEX = NEW2(ngotos + 1, Yshort);
  VERTICES = NEW2(ngotos + 1, Yshort);
  top = 0;

  R = relation;

  for (i = 0; i < ngotos; i++)
    INDEX[i] = 0;

  for (i = 0; i < ngotos; i++)
    {
      if (INDEX[i] == 0 && R[i])
	traverse(i);
    }

  FREE(INDEX);
  FREE(VERTICES);
}
