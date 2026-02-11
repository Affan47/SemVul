_e_entry_x_selection_notify_handler(void *data, int type __UNUSED__, void *event)
{
   Evas_Object *entry;
   E_Entry_Smart_Data *sd;
   Ecore_X_Event_Selection_Notify *ev;

   if ((!(entry = data)) || (!(sd = evas_object_smart_data_get(entry))))
     return EINA_TRUE;
   if (!sd->focused)
     return EINA_TRUE;

   ev = event;
   if (((ev->selection == ECORE_X_SELECTION_CLIPBOARD) ||
            (ev->selection == ECORE_X_SELECTION_PRIMARY)) &&
         (strcmp(ev->target, ECORE_X_SELECTION_TARGET_UTF8_STRING) == 0))
     {
        Ecore_X_Selection_Data_Text *text_data;

        text_data = ev->data;
        if ((text_data->data.content == ECORE_X_SELECTION_CONTENT_TEXT) &&
              (text_data->text))
          {
             char *txt = evas_textblock_text_utf8_to_markup(NULL, text_data->text);
             if (txt)
               {
                  edje_object_part_text_user_insert(sd->entry_object,
                        ENTRY_PART_NAME, txt);
                  free(txt);
               }
          }
     }

   return ECORE_CALLBACK_PASS_ON;
}
