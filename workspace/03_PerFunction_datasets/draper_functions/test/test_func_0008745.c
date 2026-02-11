_e_gadcon_cb_dnd_drop(void *data, const char *type __UNUSED__, void *event __UNUSED__)
{
   E_Gadcon *gc;
   E_Gadcon_Client *gcc = NULL;

   gc = data;

   gc->cf->clients = eina_list_append(gc->cf->clients, gc->drag_gcc->cf);
   if (!gc->new_gcc)
     {


        _e_gadcon_client_save(gc->drag_gcc);
        e_gadcon_client_show(gc->drag_gcc);
        if (gc->dnd_drop_cb) gc->dnd_drop_cb(gc, gc->drag_gcc);
        return;
     }

   e_object_del(E_OBJECT(gc->drag_gcc));
   gcc = gc->new_gcc;

   if (!gc->o_container)
     {


        gcc->cf = gc->drag_gcc->cf;
        _e_gadcon_client_save(gc->new_gcc);
        e_object_del(E_OBJECT(gc->new_gcc));
        gc->new_gcc = NULL;

        gc->drag_gcc->moving = 0;
        e_gadcon_custom_populate_request(gc);
        e_config_save_queue();
        if (gc->dnd_drop_cb) gc->dnd_drop_cb(gc, gc->drag_gcc);
        return;
     }
   if (gc->editing) e_gadcon_client_edit_begin(gc->new_gcc);
   gc->new_gcc = NULL;
   e_config_save_queue();
   if (gc->dnd_drop_cb) gc->dnd_drop_cb(gc, gc->drag_gcc);
}
