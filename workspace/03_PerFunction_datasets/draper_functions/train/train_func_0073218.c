elm_gengrid_item_show(Elm_Object_Item *item,
                      Elm_Gengrid_Item_Scrollto_Type type)
{
   Elm_Gen_Item *it = (Elm_Gen_Item *)item;
   Elm_Gengrid_Smart_Data *sd;
   Evas_Coord minx = 0, miny = 0;

   ELM_GENGRID_ITEM_CHECK_OR_RETURN(it);
   sd = GG_IT(it)->wsd;

   if ((it->generation < sd->generation)) return;
   _elm_gengrid_pan_smart_pos_min_get(sd->pan_obj, &minx, &miny);

   if (type == ELM_GENGRID_ITEM_SCROLLTO_IN)
     {

     }

   if (sd->horizontal)
     sd->s_iface->content_region_show
       (WIDGET(it), ((it->x - GG_IT(it)->prev_group) * sd->item_width)
       + (GG_IT(it)->prev_group * sd->group_item_width) + minx,
       it->y * sd->item_height + miny, sd->item_width, sd->item_height);
   else
     sd->s_iface->content_region_show
       (WIDGET(it), it->x * sd->item_width + minx,
       ((it->y - GG_IT(it)->prev_group) * sd->item_height) +
       (GG_IT(it)->prev_group * sd->group_item_height) + miny,
       sd->item_width, sd->item_height);
}
