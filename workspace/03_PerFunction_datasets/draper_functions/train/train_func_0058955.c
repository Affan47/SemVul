_theme_hook(Evas_Object *obj)
{
   Widget_Data *wd = elm_widget_data_get(obj);
   if (!wd) return;
   _elm_widget_mirrored_reload(obj);
   if (wd->scr)
     {
        const char *str;
        double scale;

        switch (wd->orient)
          {
           case ELM_PANEL_ORIENT_TOP:
             elm_widget_theme_object_set(obj, wd->scr, "panel", "top",
                                         elm_widget_style_get(obj));
             break;
           case ELM_PANEL_ORIENT_BOTTOM:
             elm_widget_theme_object_set(obj, wd->scr, "panel", "bottom",
                                         elm_widget_style_get(obj));
             break;
           case ELM_PANEL_ORIENT_LEFT:
             if (!elm_widget_mirrored_get(obj))
               elm_widget_theme_object_set(obj, wd->scr, "panel", "left",
                                           elm_widget_style_get(obj));
             else
               elm_widget_theme_object_set(obj, wd->scr, "panel", "right",
                                           elm_widget_style_get(obj));
             break;
           case ELM_PANEL_ORIENT_RIGHT:
             if (!elm_widget_mirrored_get(obj))
               elm_widget_theme_object_set(obj, wd->scr, "panel", "right",
                                           elm_widget_style_get(obj));
             else
               elm_widget_theme_object_set(obj, wd->scr, "panel", "left",
                                           elm_widget_style_get(obj));
             break;
           default:
             break;
          }
        scale = (elm_widget_scale_get(obj) * _elm_config->scale);
        edje_object_scale_set(wd->scr, scale);
        _mirrored_set(obj, elm_widget_mirrored_get(obj));
        str = edje_object_data_get(wd->scr, "focus_highlight");
        if ((str) && (!strcmp(str, "on")))
          elm_widget_highlight_in_theme_set(wd->scr, EINA_TRUE);
        else
          elm_widget_highlight_in_theme_set(wd->scr, EINA_FALSE);
     }

   _sizing_eval(obj);
}
