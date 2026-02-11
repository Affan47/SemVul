evas_object_textgrid_render_post(Evas_Object *obj)
{
   Evas_Object_Textgrid *o;


   o = (Evas_Object_Textgrid *)(obj->object_data);

   evas_object_clip_changes_clean(obj);

   evas_object_cur_prev(obj);
   o->prev = o->cur;
   o->changed = 0;

   while (eina_array_count(&o->glyphs_cleanup) > 0)
     {
        Evas_Text_Props *prop;
        unsigned int props_index;

        props_index = (unsigned int) (intptr_t) eina_array_pop(&o->glyphs_cleanup);
        prop = &(o->glyphs[props_index >> 8].props[props_index & 0xFF]);

        evas_common_text_props_content_nofree_unref(prop);
        if (!prop->info)
          {
             o->glyphs_used[props_index >> 8]--;

             if (!o->glyphs_used[props_index >> 8])
               {

               }
          }
     }
}
