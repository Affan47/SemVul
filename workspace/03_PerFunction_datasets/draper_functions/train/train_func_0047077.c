sort_bucket (ira_allocno_t *bucket_ptr,
	     int (*compare_func) (const void *, const void *))
{
  ira_allocno_t a, head;
  int n;

  for (n = 0, a = *bucket_ptr;
       a != NULL;
       a = ALLOCNO_COLOR_DATA (a)->next_bucket_allocno)
    sorted_allocnos[n++] = a;
  if (n <= 1)
    return;
  qsort (sorted_allocnos, n, sizeof (ira_allocno_t), compare_func);
  head = NULL;
  for (n--; n >= 0; n--)
    {
      a = sorted_allocnos[n];
      ALLOCNO_COLOR_DATA (a)->next_bucket_allocno = head;
      ALLOCNO_COLOR_DATA (a)->prev_bucket_allocno = NULL;
      if (head != NULL)
	ALLOCNO_COLOR_DATA (head)->prev_bucket_allocno = a;
      head = a;
    }
  *bucket_ptr = head;
}
