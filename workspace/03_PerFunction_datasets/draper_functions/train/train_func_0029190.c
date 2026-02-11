eina_hash_del_by_data(Eina_Hash *hash, const void *data)
{
   Eina_Hash_Element *hash_element;
   Eina_Hash_Head *hash_head;
   int key_hash;

   EINA_SAFETY_ON_NULL_RETURN_VAL(hash, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(data, EINA_FALSE);
   EINA_MAGIC_CHECK_HASH(hash);

   hash_element = _eina_hash_find_by_data(hash, data, &key_hash, &hash_head);
   if (!hash_element)
     goto error;

   if (hash_element->tuple.data != data)
     goto error;

   return _eina_hash_del_by_hash_el(hash, hash_element, hash_head, key_hash);

error:
   return EINA_FALSE;
}
