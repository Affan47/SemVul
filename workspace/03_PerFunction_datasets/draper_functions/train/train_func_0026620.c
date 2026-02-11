gadman_gadget_edit_end(void *data __UNUSED__, Evas_Object *obj __UNUSED__, const char *emission __UNUSED__, const char *source __UNUSED__)
{
   unsigned int layer;
   E_Gadcon_Client *drag_gcc = NULL;

   for (layer = GADMAN_LAYER_COUNT - 1; layer < UINT_MAX; layer--)
     {
        const Eina_List *l;
        E_Gadcon *gc;

        gc = eina_list_data_get(Man->gadcons[layer]);
        if (!gc) continue;
        if (!gc->editing) continue;

        evas_object_event_callback_del(Man->movers[layer], EVAS_CALLBACK_HIDE, gadman_edit);
        evas_object_hide(Man->movers[layer]);

        EINA_LIST_FOREACH(Man->gadcons[layer], l, gc)
          gc->editing = 0;
        drag_gcc = Man->drag_gcc[layer];
        Man->drag_gcc[layer] = NULL;
        break;
     }
   if (!drag_gcc) return;
   drag_gcc->gadcon->drag_gcc = NULL;
   _save_widget_position(drag_gcc);
   if (!e_object_is_del(E_OBJECT(drag_gcc)))
     e_object_unref(E_OBJECT(drag_gcc));

}
