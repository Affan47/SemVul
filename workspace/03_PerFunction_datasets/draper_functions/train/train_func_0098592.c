_overlay_group_coord_member_update(Overlay_Group *grp,
                                   Evas_Coord x,
                                   Evas_Coord y,
                                   Eina_List *members)
{
   char text[32];

   EINA_SAFETY_ON_NULL_RETURN(grp);

   if (!grp->ovl) return;

   _overlay_default_coord_set(grp->ovl, x, y);
   _coord_to_region_convert
     (grp->wsd, x, y, grp->wsd->size.w, &grp->lon, &grp->lat);

   if (grp->members) eina_list_free(grp->members);
   grp->members = members;
   snprintf(text, sizeof(text), "%d", eina_list_count(members));

   _overlay_default_layout_text_update(grp->ovl, text);
}
