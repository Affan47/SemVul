printArticleInfo (Article art, FILE *fp, unsigned int indentAmt)
{
  Buffer *b ;
  char indent [INDENT_BUFFER_SIZE] ;
  unsigned int i ;

  for (i = 0 ; i < MIN(INDENT_BUFFER_SIZE - 1,indentAmt) ; i++)
    indent [i] = ' ' ;
  indent [i] = '\0' ;

  fprintf (fp,"%sArticle : %p {\n",indent,(void *) art) ;
  fprintf (fp,"%s    article ok : %s\n",indent,boolToString (art->articleOk)) ;
  fprintf (fp,"%s    refcount : %d\n",indent,art->refCount) ;
  fprintf (fp,"%s    filename : %s\n",indent,art->fname) ;
  fprintf (fp,"%s    msgid : %s\n",indent,art->msgid) ;

  fprintf (fp,"%s    contents buffer : {\n",indent) ;
#if 0
  printBufferInfo (art->contents,fp,indentAmt + INDENT_INCR) ;
#else
  fprintf (fp,"%s    %p\n",indent,(void *) art->contents) ;
#endif

  fprintf (fp,"%s    }\n",indent) ;

  fprintf (fp,"%s    nntp buffers : {\n",indent) ;
  for (b = art->nntpBuffers ; b != NULL && *b != NULL ; b++)
#if 0
    printBufferInfo (*b,fp,indentAmt + INDENT_INCR) ;
#else
  fprintf (fp,"%s    %p\n",indent,(void *) *b) ;
#endif

  fprintf (fp,"%s    }\n", indent) ;

  fprintf (fp,"%s    logged missing : %s\n",
           indent,boolToString (art->loggedMissing));
  fprintf (fp,"%s}\n", indent) ;

}
