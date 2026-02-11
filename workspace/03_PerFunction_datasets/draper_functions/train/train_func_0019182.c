_e_int_menus_clients_sort_alpha_cb(const void *d1, const void *d2)
{
   const E_Border *bd1, *bd2;
   const char *name1, *name2;

   if (!d1) return 1;
   if (!d2) return -1;

   bd1 = d1;
   bd2 = d2;
   name1 = e_border_name_get(bd1);
   name2 = e_border_name_get(bd2);

   if (strcasecmp(name1, name2) > 0) return 1;
   if (strcasecmp(name1, name2) < 0) return -1;
   return 0;
}
