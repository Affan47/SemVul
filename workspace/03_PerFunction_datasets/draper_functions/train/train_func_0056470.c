_policy_zone_layout_update(E_Zone *zone)
{
   Eina_List *l;
   E_Border *bd;

   if (!zone) return;

   EINA_LIST_FOREACH(e_border_client_list(), l, bd)
     {

        if (bd->zone != zone) continue;


        if (e_illume_border_is_keyboard(bd)) continue;
        if (e_illume_border_is_quickpanel(bd)) continue;


        bd->changes.pos = 1;
        bd->changed = 1;
     }
}
