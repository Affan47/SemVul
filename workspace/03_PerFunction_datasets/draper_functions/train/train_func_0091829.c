_evas_render_is_relevant(Evas_Object *obj)
{
   return ((evas_object_is_visible(obj) && (!obj->cur.have_clipees)) ||
           (evas_object_was_visible(obj) && (!obj->prev.have_clipees)));
}
