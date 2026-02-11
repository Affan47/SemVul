_view_update(Evas_Object *obj)
{
   Evas_Coord width = 1, height = 1;
   Widget_Data *wd = elm_widget_data_get(obj);

   if (!wd || !wd->box || !wd->entry || !(wd->w_box > 0)) return;


   if (wd->label)
     {
        elm_box_unpack(wd->box, wd->label);
        elm_box_pack_start(wd->box, wd->label);
        evas_object_size_hint_min_get(wd->label, &width, &height);
     }

   if (wd->guidetext)
     {
        Evas_Coord guide_text_width = wd->w_box - width;
        evas_object_size_hint_min_set(wd->guidetext, guide_text_width, height);
     }


   if (wd->view_state == MULTIBUTTONENTRY_VIEW_SHRINK)
     _shrink_mode_set(obj, EINA_TRUE);


   _set_vis_guidetext(obj);
}
