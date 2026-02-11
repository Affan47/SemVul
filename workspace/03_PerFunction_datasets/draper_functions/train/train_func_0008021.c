hash_insert(void *key, void *data, struct hashtable *tab)
{
 unsigned int index = hashindex(key,tab) ;
 struct hashentry *root = tab->hashlist[ index ] ;
 if  ( hlist_update(root, key, data,  tab->compare )   != 0 ) {
          hlist_append(&(tab->hashlist[ index ]),  key, data )  ;
  tab->count ++ ;
 }
}
