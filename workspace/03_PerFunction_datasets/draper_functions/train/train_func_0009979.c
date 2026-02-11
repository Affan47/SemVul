Cudd_ApaPrintHex(
  FILE * fp,
  int  digits,
  DdApaNumber  number)
{
    int i, result;

    for (i = 0; i < digits; i++) {
	result = fprintf(fp,DD_APA_HEXPRINT,number[i]);
	if (result == EOF)
	    return(0);
    }
    return(1);

}
