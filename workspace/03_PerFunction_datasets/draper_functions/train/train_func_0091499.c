evas_object_polygon_render(Evas_Object *obj, void *output, void *context, void *surface, int x, int y)
{
   Evas_Object_Polygon *o;
   Eina_List *l;
   Evas_Polygon_Point *p;


   o = (Evas_Object_Polygon *)(obj->object_data);
   obj->layer->evas->engine.func->context_color_set(output,
                                                    context,
                                                    obj->cur.cache.clip.r,
                                                    obj->cur.cache.clip.g,
                                                    obj->cur.cache.clip.b,
                                                    obj->cur.cache.clip.a);
   obj->layer->evas->engine.func->context_multiplier_unset(output,
                                                           context);
   obj->layer->evas->engine.func->context_render_op_set(output, context,
                                                        obj->cur.render_op);
   if (o->changed)
     {
        o->engine_data = obj->layer->evas->engine.func->polygon_points_clear(obj->layer->evas->engine.data.output,
                                                                             obj->layer->evas->engine.data.context,
                                                                             o->engine_data);
        EINA_LIST_FOREACH(o->points, l, p)
          {


             o->engine_data = obj->layer->evas->engine.func->polygon_point_add(obj->layer->evas->engine.data.output,
                                                                               obj->layer->evas->engine.data.context,
                                                                               o->engine_data,
                                                                               p->x, p->y);
          }
     }

   if (o->engine_data)
     obj->layer->evas->engine.func->polygon_draw(output,
                                                 context,
                                                 surface,
                                                 o->engine_data,
                                                 o->offset.x + x, o->offset.y + y);
}
