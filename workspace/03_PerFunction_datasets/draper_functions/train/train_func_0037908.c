_cb_thumb_gen(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Coord w, h;
   Item *it = data;

   if (!it->frame) return;

   e_icon_size_get(it->thumb, &w, &h);
   edje_extern_object_aspect_set(it->thumb, EDJE_ASPECT_CONTROL_BOTH, w, h);
   evas_object_size_hint_max_set(it->thumb, w, h);
   edje_object_part_unswallow(it->frame, it->image);
   edje_object_part_swallow(it->frame, "e.swallow.thumb", it->thumb);
   evas_object_show(it->thumb);
   edje_object_signal_emit(it->frame, "e,action,thumb,show_delayed", "e");
   edje_object_message_signal_process(it->frame);
   it->have_thumb = EINA_TRUE;
   it->do_thumb = EINA_FALSE;

   if (it->image) evas_object_del(it->image);
   it->image = NULL;
}
