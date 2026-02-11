delete_partition (EquivalenceClass *partition)
{
  while (partition != NULL)
    {
      EquivalenceClass *equclass = partition;
      partition = equclass->_next;
      delete_list (equclass->_keywords);

      delete equclass;
    }
}
