eina_iterator_container_get(Eina_Iterator *iterator)
{
   EINA_MAGIC_CHECK_ITERATOR(iterator);
   EINA_SAFETY_ON_NULL_RETURN_VAL(iterator,                NULL);
   EINA_SAFETY_ON_NULL_RETURN_VAL(iterator->get_container, NULL);
   return iterator->get_container(iterator);
}
