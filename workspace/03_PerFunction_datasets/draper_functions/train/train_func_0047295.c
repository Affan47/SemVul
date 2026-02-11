evas_render_dump(Evas *e)
{
   Evas_Layer *lay;

   MAGIC_CHECK(e, Evas, MAGIC_EVAS);
   return;
   MAGIC_CHECK_END();

   EINA_INLIST_FOREACH(e->layers, lay)
     {
        Evas_Object *obj;

        EINA_INLIST_FOREACH(lay->objects, obj)
          {
             if ((obj->type) && (!strcmp(obj->type, "image")))
               evas_object_inform_call_image_unloaded(obj);
             _evas_render_dump_map_surfaces(obj);
          }
     }
   if ((e->engine.func) && (e->engine.func->output_dump) &&
       (e->engine.data.output))
     e->engine.func->output_dump(e->engine.data.output);
}
