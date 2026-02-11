_sort_widget_themes(const void *data1, const void *data2)
{
   const char *d1, *d2;

   d1 = data1;
   d2 = data2;
   if (!d1) return 1;
   if (!d2) return -1;

   return strcmp(d1, d2);
}
