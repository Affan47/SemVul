_e_smart_event_mouse_up(void *data, Evas *e __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info)
{
   Evas_Event_Mouse_Down *ev;
   E_Smart_Data *sd;

   sd = data;
   ev = event_info;
   if (ev->button == 1)
     {
	if (!sd->down_cancel)
	  {
	     edje_object_signal_emit(sd->edje_obj, "e,state,slide,hint,off", "e");
	     if (!(ev->event_flags & EVAS_EVENT_FLAG_ON_HOLD))
	       {
		  if (sd->cur)
		    {


			 {
			    edje_object_signal_emit(sd->edje_obj, "e,action,select", "e");
			    if (sd->cur->func) sd->cur->func(sd->cur->data);
			 }
		    }
	       }
	  }
	sd->down = 0;
     }
}
