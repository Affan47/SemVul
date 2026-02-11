eina_hash_foreach(const Eina_Hash *hash,
                  Eina_Hash_Foreach func,
                  const void *fdata)
{
   Eina_Iterator *it;
   Eina_Hash_Foreach_Data foreach;

   EINA_MAGIC_CHECK_HASH(hash);
   EINA_SAFETY_ON_NULL_RETURN(hash);
   EINA_SAFETY_ON_NULL_RETURN(func);

   foreach.cb = func;
   foreach.fdata = fdata;

   it = eina_hash_iterator_tuple_new(hash);
   if (!it)
     return;
   eina_iterator_foreach(it, EINA_EACH_CB(_eina_foreach_cb), &foreach);

   eina_iterator_free(it);
}
