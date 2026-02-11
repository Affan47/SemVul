newArticle (const char *filename, const char *msgid)
{
  Article newArt = NULL ;

  if (hashTable == NULL)
    {
      int i ;

      ASSERT ((TABLE_SIZE & HASH_MASK) == 0) ;
      hashTable = ALLOC (HashEntry, TABLE_SIZE) ;
      ASSERT (hashTable != NULL) ;

      addPointerFreedOnExit ((char *)hashTable) ;

      for (i = 0 ; i < TABLE_SIZE ; i++)
        hashTable [i] = NULL ;

      if (ARTICLE_STATS_PERIOD > 0)
        articleStatsId = prepareSleep (logArticleStats,ARTICLE_STATS_PERIOD,0);
    }


  if ((newArt = hashFindArticle (msgid)) == NULL)
    {
      newArt = CALLOC (struct article_s, 1) ;
      ASSERT (newArt != NULL) ;

      newArt->fname = MALLOC (strlen (filename) + 1) ;
      ASSERT (newArt->fname != NULL) ;
      strcpy (newArt->fname,filename) ;

      newArt->msgid = MALLOC (strlen (msgid) + 1) ;
      ASSERT (newArt->msgid != NULL) ;
      strcpy (newArt->msgid,msgid) ;

      newArt->contents = NULL ;
      newArt->mMapping = NULL ;
      newArt->refCount = 1 ;
      newArt->loggedMissing = false ;
      newArt->articleOk = true ;
      newArt->inWireFormat = false ;

      dprintf (3,"Adding a new article(%p): %s\n", newArt, msgid) ;

      articlesInUse++ ;
      articleTotal++ ;

      hashAddArticle (newArt) ;
    }
  else
    {
      if (strcmp (filename,newArt->fname) != 0)
        syslog (LOG_ERR, DOUBLE_NAME, filename, newArt->fname) ;

      newArt->refCount++ ;
      dprintf (2,"Reusing existing article for %s\nx",msgid) ;
    }

  return newArt ;
}
