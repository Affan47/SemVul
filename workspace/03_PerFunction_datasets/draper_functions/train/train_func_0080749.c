markexts(block *vbm, const ExtDataRec *exts)
{
  int i;
  unsigned int pt, len;

  for (i = 0; i < 3; ++i)
    {
      for ( pt = (*exts)[i].xdrStABN,
	   len = (*exts)[i].xdrNumABlks; len--; ++pt)
	BMSET(vbm, pt);
    }
}
