_eina_hash_iterator_free(Eina_Iterator_Hash *it)
{
   EINA_MAGIC_CHECK_HASH_ITERATOR(it);
   if (it->current)
     eina_iterator_free(it->current);

   if (it->list)
     eina_iterator_free(it->list);

   free(it);
}
