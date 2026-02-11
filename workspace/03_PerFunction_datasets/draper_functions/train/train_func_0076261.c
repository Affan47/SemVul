hashAddArticle (Article article)
{
  u_int hash = hashString (article->msgid) ;
  HashEntry h ;
  HashEntry ne ;

  h = hashTable [TABLE_ENTRY(hash)] ;

  ne = ALLOC (struct hash_entry_s, 1) ;
  ASSERT (ne != NULL) ;

  ne->article = article ;
  ne->hash = hash ;
  ne->next = hashTable [TABLE_ENTRY(hash)] ;
  ne->prev = NULL ;

  if (h != NULL)
    h->prev = ne ;

  hashTable [TABLE_ENTRY(hash)] = ne ;

  ne->nextTime = chronList ;
  ne->prevTime = NULL ;

  if (chronList != NULL)
    chronList->prevTime = ne ;

  chronList = ne ;
}
