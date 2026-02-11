_ecore_evas_ews_render(Ecore_Evas *ee)
{
   Eina_List *updates = NULL, *l, *ll;
   Ecore_Evas *ee2;
   Eina_Rectangle *r;
   int w, h, rend = 0;
   void *pixels;

   EINA_LIST_FOREACH(ee->sub_ecore_evas, ll, ee2)
     {
        if (ee2->func.fn_pre_render) ee2->func.fn_pre_render(ee2);
        rend |= _ecore_evas_ews_render(ee2);
        if (ee2->func.fn_post_render) ee2->func.fn_post_render(ee2);
     }

   evas_object_image_size_get(ee->engine.ews.image, &w, &h);
   if ((w != ee->w) || (h != ee->h))
     ecore_evas_resize(ee, w, h);

   pixels = evas_object_image_data_get(ee->engine.ews.image, 1);
   if (pixels)
     {
        updates = evas_render_updates(ee->evas);
     }
   evas_object_image_data_set(ee->engine.ews.image, pixels);

   EINA_LIST_FOREACH(updates, l, r)
     evas_object_image_data_update_add(ee->engine.ews.image,
                                       r->x, r->y, r->w, r->h);

   if (updates)
     {
        evas_render_updates_free(updates);
        _ecore_evas_idle_timeout_update(ee);
     }

   return updates ? 1 : rend;
}
