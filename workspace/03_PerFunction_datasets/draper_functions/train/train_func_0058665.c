foreign_key_prefix(Key *a, Key *b)
{

  if (a->generated)
  {
    if (b->generated && a->columns.elements > b->columns.elements)
      swap_variables(Key*, a, b);
  }
  else
  {
    if (!b->generated)
      return TRUE;
    swap_variables(Key*, a, b);
  }


  if (a->columns.elements > b->columns.elements)
    return TRUE;

  List_iterator<Key_part_spec> col_it1(a->columns);
  List_iterator<Key_part_spec> col_it2(b->columns);
  const Key_part_spec *col1, *col2;

#ifdef ENABLE_WHEN_INNODB_CAN_HANDLE_SWAPED_FOREIGN_KEY_COLUMNS
  while ((col1= col_it1++))
  {
    bool found= 0;
    col_it2.rewind();
    while ((col2= col_it2++))
    {
      if (*col1 == *col2)
      {
        found= TRUE;
	break;
      }
    }
    if (!found)
      return TRUE;
  }
  return FALSE;
#else
  while ((col1= col_it1++))
  {
    col2= col_it2++;
    if (!(*col1 == *col2))
      return TRUE;
  }
  return FALSE;
#endif
}
