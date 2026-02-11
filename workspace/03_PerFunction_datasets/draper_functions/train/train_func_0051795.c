bitmap_initialize (head, using_obstack)
     bitmap head;
     int using_obstack;
{
  if (head == NULL && ! using_obstack)
    head = ggc_alloc (sizeof (*head));

  head->first = head->current = 0;
  head->using_obstack = using_obstack;

  return head;
}
