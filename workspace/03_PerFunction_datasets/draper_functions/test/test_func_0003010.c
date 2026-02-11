e_shelf_style_set(E_Shelf *es, const char *style)
{
   const char *option;
   char buf[1024];

   E_OBJECT_CHECK(es);
   E_OBJECT_TYPE_CHECK(es, E_SHELF_TYPE);

   if (!es->o_base) return;
   if (style != es->style)
     eina_stringshare_replace(&es->style, style);

   if (style)
     snprintf(buf, sizeof(buf), "e/shelf/%s/base", style);
   else
     snprintf(buf, sizeof(buf), "e/shelf/%s/base", "default");

   if (!e_theme_edje_object_set(es->o_base, "base/theme/shelf", buf))
     e_theme_edje_object_set(es->o_base, "base/theme/shelf",
                             "e/shelf/default/base");

   option = edje_object_data_get(es->o_base, "hidden_state_size");
   if (option)
     es->hidden_state_size = atoi(option);
   else
     es->hidden_state_size = 4;
   option = edje_object_data_get(es->o_base, "instant_delay");
   if (option)
     es->instant_delay = atof(option);
   else
     es->instant_delay = -1.0;

   if (es->popup) e_popup_edje_bg_object_set(es->popup, es->o_base);
}
