gadman_gadget_place(E_Gadcon_Client *gcc, const E_Gadcon_Client_Class *cc, E_Config_Gadcon_Client *cf, Gadman_Layer_Type layer, E_Zone *zone)
{
   E_Gadcon *gc;
   Eina_List *l;

   if (!cf->name) return NULL;

   gc = gadman_gadcon_get(zone, layer);
   if (!cc)
     {
        EINA_LIST_FOREACH(gc->populated_classes, l, cc)
          {
             if (!strcmp(cc->name, cf->name))
               break;
             else
               cc = NULL;
          }
     }


   if (!cc)
     {
        e_gadcon_client_queue(gc, cf);
        e_gadcon_custom_populate_request(gc);
        return NULL;
     }


   if (!gcc)
     {
        gcc = cc->func.init(gc, cf->name, cf->id, cc->default_style);
        if (!gcc) return NULL;
        e_object_delfn_add(E_OBJECT(gcc), _gadman_gadget_free, NULL);
        gcc->cf = cf;
        gcc->client_class = cc;


        if (cc->func.orient)
          cc->func.orient(gcc, gcc->cf->orient);
     }

   Man->gadgets[layer] = eina_list_append(Man->gadgets[layer], cf);


   gcc->o_frame = edje_object_add(gc->evas);
   e_theme_edje_object_set(gcc->o_frame, "base/theme/gadman", "e/gadman/frame");

   if ((cf->style) && (!strcmp(cf->style, E_GADCON_CLIENT_STYLE_INSET)))
     edje_object_signal_emit(gcc->o_frame, "e,state,visibility,inset", "e");
   else
     edje_object_signal_emit(gcc->o_frame, "e,state,visibility,plain", "e");


   edje_object_part_swallow(gcc->o_frame, "e.swallow.content", gcc->o_base);
   evas_object_event_callback_add(gcc->o_frame, EVAS_CALLBACK_MOUSE_DOWN,
                                  on_frame_click, gcc);

   if (gcc->gadcon->id == ID_GADMAN_LAYER_TOP)
     edje_object_signal_emit(gcc->o_frame, "e,state,visibility,hide", "e");
   if (cc->name)
     {
        l = eina_hash_find(_gadman_gadgets, cc->name);
        eina_hash_set(_gadman_gadgets, cc->name, eina_list_append(l, gcc->cf));
     }
   ecore_job_add((Ecore_Cb)gadman_gadcon_place_job, gcc);

   return gcc;
}
