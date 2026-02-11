_e_gadcon_cb_dnd_move(void *data, const char *type __UNUSED__, void *event)
{
   E_Event_Dnd_Move *ev;
   E_Gadcon *gc;
   E_Gadcon_Client *gcc = NULL;
   int dx = 0, dy = 0;
   Evas_Object *o;

   ev = event;
   gc = data;

   gcc = gc->new_gcc ?: gc->drag_gcc;
   if (!gcc) return;

   if (gcc->state_info.resist > 0)
     {
        gcc->state_info.resist--;
        return;
     }
   e_gadcon_layout_freeze(gc->o_container);

   if (e_gadcon_layout_orientation_get(gc->o_container))
     gcc->config.pos = ev->x - gcc->config.size / 2;
   else
     gcc->config.pos = ev->y - gcc->config.size / 2;
   if (!gcc->gadcon->o_container)
     {
        int w, h;
        w = gc->zone->w;
        h = gc->zone->h;
        gcc->config.pos_x = (double)ev->x / (double)w;
        gcc->config.pos_y = (double)ev->y / (double)h;
        if (gcc->o_frame) evas_object_move(gcc->o_frame, ev->x, ev->y);
        else if (gcc->o_base) evas_object_move(gcc->o_base, ev->x, ev->y);
     }
   else
     evas_object_geometry_get(gc->o_container, &dx, &dy, NULL, NULL);
   _e_gadcon_client_inject(gc, gcc, ev->x + dx, ev->y + dy);

   o = gcc->o_frame ? gcc->o_frame : gcc->o_base;
   if (o)
     e_gadcon_layout_pack_request_set(o, gcc->config.pos,
                                      gcc->config.size);
   e_gadcon_layout_thaw(gc->o_container);
   if (gc->dnd_move_cb) gc->dnd_move_cb(gc, gcc);
}
