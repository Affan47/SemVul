_eval_instance_size(Instance *inst)
{
   Evas_Coord mw, mh, omw, omh;

   edje_object_size_min_get(inst->o_clock, &mw, &mh);
   omw = mw;
   omh = mh;

   if ((mw < 1) || (mh < 1))
     {
        Evas_Coord x, y, sw = 0, sh = 0, ow, oh;
        Eina_Bool horiz;
        const char *orient;

        switch (inst->gcc->gadcon->orient)
          {
           case E_GADCON_ORIENT_TOP:
           case E_GADCON_ORIENT_CORNER_TL:
           case E_GADCON_ORIENT_CORNER_TR:
           case E_GADCON_ORIENT_BOTTOM:
           case E_GADCON_ORIENT_CORNER_BL:
           case E_GADCON_ORIENT_CORNER_BR:
           case E_GADCON_ORIENT_HORIZ:
             horiz = EINA_TRUE;
             orient = "e,state,horizontal";
             break;

           case E_GADCON_ORIENT_LEFT:
           case E_GADCON_ORIENT_CORNER_LB:
           case E_GADCON_ORIENT_CORNER_LT:
           case E_GADCON_ORIENT_RIGHT:
           case E_GADCON_ORIENT_CORNER_RB:
           case E_GADCON_ORIENT_CORNER_RT:
           case E_GADCON_ORIENT_VERT:
             horiz = EINA_FALSE;
             orient = "e,state,vertical";
             break;

           default:
             horiz = EINA_TRUE;
             orient = "e,state,float";
          }

        if (inst->gcc->gadcon->shelf)
          {
             if (horiz)
               sh = inst->gcc->gadcon->shelf->h;
             else
               sw = inst->gcc->gadcon->shelf->w;
          }

        evas_object_geometry_get(inst->o_clock, NULL, NULL, &ow, &oh);
        if (orient)
          edje_object_signal_emit(inst->o_clock, orient, "e");
        evas_object_resize(inst->o_clock, sw, sh);
        edje_object_message_signal_process(inst->o_clock);

        edje_object_parts_extends_calc(inst->o_clock, &x, &y, &mw, &mh);
        evas_object_resize(inst->o_clock, ow, oh);
     }

   if (mw < 4) mw = 4;
   if (mh < 4) mh = 4;

   if (mw < omw) mw = omw;
   if (mh < omh) mh = omh;

   e_gadcon_client_aspect_set(inst->gcc, mw, mh);
   e_gadcon_client_min_size_set(inst->gcc, mw, mh);
}
