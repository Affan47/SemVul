_e_gadcon_cb_dnd_leave(void *data, const char *type __UNUSED__, void *event __UNUSED__)
{
   E_Gadcon *gc;

   gc = data;


   if (gc->drag_gcc->gadcon == gc) e_gadcon_client_hide(gc->drag_gcc);


   if (!gc->new_gcc)
     {
        if (gc->dnd_leave_cb) gc->dnd_leave_cb(gc, gc->drag_gcc);
        return;
     }


   e_object_del(E_OBJECT(gc->new_gcc));
   gc->new_gcc = NULL;
   evas_object_show(gc->drag_gcc->drag.drag->object);
   if (gc->dnd_leave_cb) gc->dnd_leave_cb(gc, gc->drag_gcc);
}
