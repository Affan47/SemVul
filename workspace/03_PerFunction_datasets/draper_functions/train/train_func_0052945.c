_eina_hash_el_free(Eina_Hash_Element *hash_element, Eina_Hash *hash)
{
   if (hash->data_free_cb)
     hash->data_free_cb(hash_element->tuple.data);

   if (hash_element->begin == EINA_FALSE)
     free(hash_element);
}
