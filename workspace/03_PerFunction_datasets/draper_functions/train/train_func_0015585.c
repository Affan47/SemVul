ishc(char *buf_start, char *hchar)
{

  if (*hchar != '#')
	return(0);
  if (hchar == buf_start)
	return(1);
  if (!isws(*(hchar - 1)))
	return(0);
  return(1);
}
