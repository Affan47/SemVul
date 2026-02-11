gPrintHostInfo (FILE *fp, unsigned int indentAmt)
{
  Host h ;
  char indent [INDENT_BUFFER_SIZE] ;
  unsigned int i ;

  for (i = 0 ; i < MIN(INDENT_BUFFER_SIZE - 1,indentAmt) ; i++)
    indent [i] = ' ' ;
  indent [i] = '\0' ;

  fprintf (fp,"%sGlobal Host list : (count %d) {\n",indent,gHostCount) ;

  for (h = gHostList ; h != NULL ; h = h->next)
    printHostInfo (h,fp,indentAmt + INDENT_INCR) ;

  fprintf (fp,"%s}\n",indent) ;
}
