_item_position(Elm_Gen_Item *it,
               Evas_Object *view,
               Evas_Coord it_x,
               Evas_Coord it_y)
{
   if (!it) return;
   if (!view) return;

   evas_event_freeze
     (evas_object_evas_get(ELM_WIDGET_DATA(GL_IT(it)->wsd)->obj));
   evas_object_resize(view, it->item->w, it->item->h);
   evas_object_move(view, it_x, it_y);
   evas_object_show(view);
   evas_event_thaw(evas_object_evas_get(ELM_WIDGET_DATA(GL_IT(it)->wsd)->obj));
   evas_event_thaw_eval
     (evas_object_evas_get(ELM_WIDGET_DATA(GL_IT(it)->wsd)->obj));
}
