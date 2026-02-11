SearchAscList (const tlist_t *SearchList, int value)


{
   const tlist_t *pos = SearchList;

   while (pos && pos->value < value)
      pos = pos->next;

   if (pos && pos->value == value)
      return YES;
   else
      return NO;
}
