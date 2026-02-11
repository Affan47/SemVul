_item_multi_move_cb(void *data,
                    Evas *evas __UNUSED__,
                    Evas_Object *obj __UNUSED__,
                    void *event_info)
{
   Elm_Gen_Item *it = data;
   Evas_Event_Multi_Move *ev = event_info;

   if (GL_IT(it)->wsd->multi_device != ev->device) return;
   GL_IT(it)->wsd->cur_mx = ev->cur.canvas.x;
   GL_IT(it)->wsd->cur_my = ev->cur.canvas.y;
}
