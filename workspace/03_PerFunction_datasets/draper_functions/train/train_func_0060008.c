_elm_scroll_scroll_bar_reset(Elm_Scrollable_Smart_Interface_Data *sid)
{
   Evas_Coord px = 0, py = 0, minx = 0, miny = 0;

   if (!sid->edje_obj) return;

   edje_object_part_drag_value_set
     (sid->edje_obj, "elm.dragable.vbar", 0.0, 0.0);
   edje_object_part_drag_value_set
     (sid->edje_obj, "elm.dragable.hbar", 0.0, 0.0);
   if ((!sid->content) && (!sid->extern_pan))
     {
        edje_object_part_drag_size_set
          (sid->edje_obj, "elm.dragable.vbar", 1.0, 1.0);
        edje_object_part_drag_size_set
          (sid->edje_obj, "elm.dragable.hbar", 1.0, 1.0);
     }
   if (sid->pan_obj)
     {
        ELM_PAN_DATA_GET_OR_RETURN(sid->pan_obj, psd);

        psd->api->pos_min_get(sid->pan_obj, &minx, &miny);
        psd->api->pos_get(sid->pan_obj, &px, &py);
        psd->api->pos_set(sid->pan_obj, minx, miny);
     }
   if ((px != minx) || (py != miny))
     edje_object_signal_emit(sid->edje_obj, "elm,action,scroll", "elm");
   _elm_direction_arrows_eval(sid);
}
