gadman_gadgets_show(void)
{
   Eina_List *l, *ll;
   E_Gadcon_Client *gcc;
   E_Config_Gadcon_Client *cf_gcc;

   Man->visible = 1;
   ecore_evas_show(Man->top_ee);

   if (Man->conf->bg_type == BG_STD)
     {
        if (Man->conf->anim_bg)
          edje_object_signal_emit(Man->full_bg,
                                  "e,state,visibility,show", "e");
        else
          edje_object_signal_emit(Man->full_bg,
                                  "e,state,visibility,show,now", "e");
     }
   else
     {
        if (Man->conf->anim_bg)
          edje_object_signal_emit(Man->full_bg,
                                  "e,state,visibility,show,custom", "e");
        else
          edje_object_signal_emit(Man->full_bg,
                                  "e,state,visibility,show,custom,now", "e");
     }


   EINA_LIST_FOREACH_SAFE(Man->gadgets[GADMAN_LAYER_TOP], l, ll, cf_gcc)
     {
        gcc = e_gadcon_client_find(NULL, cf_gcc);
        if (!gcc)
          {
             Man->gadgets[GADMAN_LAYER_TOP] = eina_list_remove_list(Man->gadgets[GADMAN_LAYER_TOP], l);
             continue;
          }
        if (Man->conf->anim_gad)
          edje_object_signal_emit(gcc->o_frame,
                                  "e,state,visibility,show", "e");
        else
          edje_object_signal_emit(gcc->o_frame,
                                  "e,state,visibility,show,now", "e");
     }
}
