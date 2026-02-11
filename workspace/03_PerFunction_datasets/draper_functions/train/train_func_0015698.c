clean_up(queue_item *p)
{
dest_item *dd = p->destinations;
while (dd != NULL)
  {
  dest_item *next = dd->next;
  store_free(dd);
  dd = next;
  }
if (p->sender != NULL) store_free(p->sender);
store_free(p);
}
