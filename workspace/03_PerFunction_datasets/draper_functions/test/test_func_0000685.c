resolve(ParamElem plst[])
{
  int i;

  if (allLength > 0) return;


  for (i=0; plst[i].code != EOF; i++)
    if (plst[i].code < LITMIN)
      if (!isHere(plst[i].code)) {
	params[0] = plst[i];
	params[1].code = EOF;
	error(M_NO_SUCH);
      }
}
