_cb_desks_name(const void *data1, const void *data2)
{
   const Efreet_Desktop *d1;
   const char *d2;

   if (!(d1 = data1)) return 1;
   if (!d1->name) return 1;
   if (!(d2 = data2)) return -1;
   return strcmp(d1->name, d2);
}
