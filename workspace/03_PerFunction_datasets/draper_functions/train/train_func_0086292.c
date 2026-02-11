merge (List_Node *list1, List_Node *list2)
{
  if (list1 == 0)
    {
      return list2;
    }
  else if (list2 == 0)
    {
      return list1;
    }
  else if ((occurrence_sort && list1->occurrence < list2->occurrence)
           || (hash_sort && list1->hash_value > list2->hash_value)
           || (key_sort && ACE_OS::strcmp (list1->key, list2->key) >= 0))
    {
      list2->next = merge (list2->next, list1);
      return list2;
    }
  else
    {
      list1->next = merge (list1->next, list2);
      return list1;
    }
}
