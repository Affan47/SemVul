_e_fm2_icons_place_custom_grid_icons(E_Fm2_Smart_Data *sd)
{

   Eina_List *l;
   E_Fm2_Icon *ic;

   EINA_LIST_FOREACH(sd->icons, l, ic)
     {
        if (!ic->saved_pos)
          {

          }

        if ((ic->x + ic->w) > sd->max.w) sd->max.w = ic->x + ic->w;
        if ((ic->y + ic->h) > sd->max.h) sd->max.h = ic->y + ic->h;
        sd->min.w = MAX(ic->min_w, sd->min.w);
        sd->min.h = MAX(ic->min_h, sd->min.h);
     }
}
