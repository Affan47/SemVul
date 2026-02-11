_evas_object_text_item_new(Evas_Object *obj, Evas_Object_Text *o,
      Evas_Font_Instance *fi, const Eina_Unicode *str, Evas_Script_Type script,
      size_t pos, size_t visual_pos, size_t len)
{
   Evas_Object_Text_Item *it;

   it = calloc(1, sizeof(Evas_Object_Text_Item));
   it->text_pos = pos;
   it->visual_pos = visual_pos;
   evas_common_text_props_bidi_set(&it->text_props, o->bidi_par_props,
         it->text_pos);
   evas_common_text_props_script_set(&it->text_props, script);

   if (fi)
     {
        ENFN->font_text_props_info_create(ENDT,
              fi, str + pos, &it->text_props,
              o->bidi_par_props, it->text_pos, len, EVAS_TEXT_PROPS_MODE_SHAPE);

        ENFN->font_string_size_get(ENDT,
              o->font,
              &it->text_props,
              &it->w, &it->h);
        it->adv = ENFN->font_h_advance_get(ENDT, o->font,
              &it->text_props);
     }
   o->items = (Evas_Object_Text_Item *)
      eina_inlist_append(EINA_INLIST_GET(o->items), EINA_INLIST_GET(it));
   return it;
}
