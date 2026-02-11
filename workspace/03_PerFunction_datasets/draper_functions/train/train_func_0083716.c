attributes_copy (Attributes *target, const Attributes *source)
{
  if (hashtable_count (source->table) > 0)
  {
    struct hashtable_itr *i = hashtable_iterator (source->table);

    do
    {
      const Value *value = hashtable_iterator_value (i);

      attributes_set (target, hashtable_iterator_key (i), value_clone (value));
    } while (hashtable_iterator_advance (i));

    free (i);
  }

  return target;
}
