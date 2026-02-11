my_feof(FILE *fp)
{
     int	c;

     if ((c = fgetc(fp)) == EOF) {
	  return TRUE;
     } else {
	  ungetc(c, fp);
	  return FALSE;
     }
}
