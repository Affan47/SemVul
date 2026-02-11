gl16_content_get(void *data, Evas_Object *obj, const char *part)
{
   Testitem *tit = data;
   char buf[PATH_MAX];

   if (!strcmp(part, "elm.text.flip"))
     {
        Evas_Object *btn = elm_button_add(obj);
        elm_object_text_set(btn, "flipped content placement");
        evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
        evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, 0.0);
        evas_object_smart_callback_add(btn, "clicked", _flip_icon_clicked_cb, (void *)tit);
        evas_object_show(btn);
        return btn;
     }
   else if (!strcmp(part, "elm.edit.icon.1"))
     {
        Evas_Object *icn = elm_icon_add(obj);
        snprintf(buf, sizeof(buf), "%s/images/icon_04.png", PACKAGE_DATA_DIR);
        elm_image_file_set(icn, buf, NULL);
        evas_object_propagate_events_set(icn, EINA_FALSE);
        evas_object_size_hint_aspect_set(icn, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
        return icn;
     }
   else if (!strcmp(part, "elm.edit.icon.2"))
     {
        Evas_Object *icn = elm_icon_add(obj);
        snprintf(buf, sizeof(buf), "%s/images/icon_09.png", PACKAGE_DATA_DIR);
        elm_image_file_set(icn, buf, NULL);
        evas_object_propagate_events_set(icn, EINA_FALSE);
        evas_object_size_hint_aspect_set(icn, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
        evas_object_smart_callback_add(icn, "clicked", _flip_icon_clicked_cb, (void *)tit);
        return icn;
     }
   else return NULL;
}
