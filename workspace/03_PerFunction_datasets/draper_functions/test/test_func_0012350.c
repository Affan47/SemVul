_e_mod_sft_win_cb_free(Sft_Win *swin)
{
   Ecore_Event_Handler *hdl;
   const Evas_Object *box;


   EINA_LIST_FREE(swin->hdls, hdl)
     ecore_event_handler_del(hdl);

   if ((box = edje_object_part_object_get(swin->o_base, "e.box.buttons")))
     {
        Evas_Object *btn;


        EINA_LIST_FREE(swin->btns, btn)
          {
             edje_object_part_box_remove(swin->o_base, "e.box.buttons", btn);
             evas_object_del(btn);
          }
     }
   if ((box = edje_object_part_object_get(swin->o_base, "e.box.extra_buttons")))
     {
        Evas_Object *btn;


        EINA_LIST_FREE(swin->extra_btns, btn)
          {
             edje_object_part_box_remove(swin->o_base,
                                         "e.box.extra_buttons", btn);
             evas_object_del(btn);
          }
     }


   if (swin->o_base) evas_object_del(swin->o_base);
   swin->o_base = NULL;


   if (swin->win) e_object_del(E_OBJECT(swin->win));
   swin->win = NULL;


   ecore_x_e_illume_softkey_geometry_set(swin->zone->black_win, 0, 0, 0, 0);


   E_FREE(swin);
}
