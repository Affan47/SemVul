e_slidecore_jump(Evas_Object *obj, int num)
{
   API_ENTRY return;

   sd->slide_start_pos = sd->pos;
   sd->slide_pos = num * sd->dist;
   if (!sd->slide_animator)
     sd->slide_animator = ecore_animator_add(_e_smart_cb_slide_animator,
					     sd);
   sd->slide_start = ecore_loop_time_get();
}
