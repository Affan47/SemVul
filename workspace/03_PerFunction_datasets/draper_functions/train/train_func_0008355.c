_e_fm2_region_unrealize(E_Fm2_Region *rg)
{
   Eina_List *l;
   E_Fm2_Icon *ic;

   if (!rg->realized) return;

   rg->realized = 0;
   edje_freeze();
   EINA_LIST_FOREACH(rg->list, l, ic)
     _e_fm2_icon_unrealize(ic);
   edje_thaw();
}
