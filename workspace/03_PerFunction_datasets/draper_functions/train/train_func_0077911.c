Myqsort(void* bot, int nmemb, int size, CompareFunc compar)
{
  if (nmemb <= 1) return;

  if (nmemb >= THRESH) quick_sort((char*)bot, nmemb, size, compar);
  else insertion_sort((char*)bot, nmemb, size, compar);
}
