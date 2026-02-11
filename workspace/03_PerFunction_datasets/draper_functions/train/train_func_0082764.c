attributes_iter_next (AttributesIter *iter)
{
  if (iter->has_next)
  {
    iter->has_next =
      hashtable_iterator_advance ((struct hashtable_itr *)&iter->hash_iter);
  }

  return iter->has_next;
}
