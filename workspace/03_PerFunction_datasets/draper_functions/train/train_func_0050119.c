_mouse_move(void *data __UNUSED__, Evas *e __UNUSED__, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Event_Mouse_Move *ev;
   ev = (Evas_Event_Mouse_Move *)event_info;
   GLData *gld = evas_object_data_get(obj, "gld");
   float dx = 0, dy = 0;

   if (gld->mouse_down)
     {
        dx = ev->cur.canvas.x - ev->prev.canvas.x;
        dy = ev->cur.canvas.y - ev->prev.canvas.y;

        gld->view_roty += -1.0 * dx;
        gld->view_rotx += -1.0 * dy;
     }
}
