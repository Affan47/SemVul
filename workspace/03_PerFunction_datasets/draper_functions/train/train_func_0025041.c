_evas_object_text_recalc(Evas_Object *obj)
{
   Evas_Object_Text *o;
   Eina_Unicode *text = NULL;
   o = (Evas_Object_Text *)(obj->object_data);

   if (o->items) _evas_object_text_items_clear(o);
   if (o->cur.utf8_text)
     text = eina_unicode_utf8_to_unicode(o->cur.utf8_text,
           NULL);

   if (!text) text = eina_unicode_strdup(EINA_UNICODE_EMPTY_STRING);

   _evas_object_text_layout(obj, o, text);

   if (text) free(text);


   if (o->items)
     {
        Evas_Object_Text_Item *item;

        for (item = o->items ; item ;
              item = EINA_INLIST_CONTAINER_GET(
                 EINA_INLIST_GET(item)->next, Evas_Object_Text_Item))
          {
             int asc = 0, desc = 0;


             if (!item->text_props.font_instance) continue;

             asc = evas_common_font_instance_ascent_get(item->text_props.font_instance);
             desc = evas_common_font_instance_descent_get(item->text_props.font_instance);
             if (asc > o->ascent) o->ascent = asc;
             if (desc > o->descent) o->descent = desc;

             asc = evas_common_font_instance_max_ascent_get(item->text_props.font_instance);
             desc = evas_common_font_instance_max_descent_get(item->text_props.font_instance);
             if (asc > o->max_ascent) o->max_ascent = asc;
             if (desc > o->max_descent) o->max_descent = desc;
          }
     }
   else if (o->font)
     {
        o->ascent = ENFN->font_ascent_get(ENDT, o->font);
        o->descent = ENFN->font_descent_get(ENDT, o->font);
        o->max_ascent = ENFN->font_max_ascent_get(ENDT, o->font);
        o->max_descent = ENFN->font_max_descent_get(ENDT, o->font);
     }

   if ((o->font) && (o->items))
     {
	int w, h;
	int l = 0, r = 0, t = 0, b = 0;

        w = _evas_object_text_horiz_advance_get(obj, o);
        h = _evas_object_text_vert_advance_get(obj, o);
	evas_text_style_pad_get(o->cur.style, &l, &r, &t, &b);
	obj->cur.geometry.w = w + l + r;
        obj->cur.geometry.h = h + t + b;

     }
   else
     {
	int t = 0, b = 0;

	evas_text_style_pad_get(o->cur.style, NULL, NULL, &t, &b);
	obj->cur.geometry.w = 0;
        obj->cur.geometry.h = o->max_ascent + o->max_descent + t + b;

     }
   evas_object_clip_dirty(obj);
}
