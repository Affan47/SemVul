compare_line_list (list1, lengths1, list2, lengths2, nl)
     char * const list1[], * const list2[];
     size_t const lengths1[], lengths2[];
     int nl;
{
  char
    * const *l1 = list1,
    * const *l2 = list2;
  size_t const
    *lgths1 = lengths1,
    *lgths2 = lengths2;

  while (nl--)
    if (!*l1 || !*l2 || *lgths1 != *lgths2++
	|| memcmp (*l1++, *l2++, *lgths1++))
      return 0;
  return 1;
}
