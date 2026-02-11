hash_free(struct hashtable *tab)
{
 int i ;
 struct hashentry *pos;

 for (i=0; i< tab->hashsize ; i++)
  for  (pos = tab->hashlist[ i ] ; NULL != pos; pos = hashentry_free(pos)) ;
 free(tab->hashlist) ;
 free(tab) ;
 tab =NULL ;
}
