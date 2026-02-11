_policy_zone_move_resize(E_Zone *zone)
{
   Eina_List *l;
   E_Border *bd;


   if (!zone) return;

   EINA_LIST_FOREACH(e_border_client_list(), l, bd)
     {

        if (bd->zone != zone) continue;


        bd->changes.pos = 1;
        bd->changed = 1;
     }
}
