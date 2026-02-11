unlink(Record **list)
{
   if (next)
      next->prev = prev;
   if (prev)
      prev->next = next;
   else
      *list = next;
}
