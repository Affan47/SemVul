e_illume_border_softkey_pos_get(E_Zone *zone, int *x, int *y)
{
   E_Border *sft;

   if (x) *x = 0;
   if (y) *y = 0;


   if (!zone) return;


   if (x) *x = zone->x;
   if (y) *y = zone->y;


   if (!(sft = e_illume_border_softkey_get(zone))) return;


   if (x) *x = sft->x;
   if (y) *y = sft->y;
}
