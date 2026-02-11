_position_change_magnetic_cb(void *data __UNUSED__, Evas_Object * obj, void *event_info)
{
   if (!strcmp((char *)event_info, "left"))
     elm_actionslider_magnet_pos_set(obj, ELM_ACTIONSLIDER_LEFT);
   else if (!strcmp((char *)event_info, "right"))
     elm_actionslider_magnet_pos_set(obj, ELM_ACTIONSLIDER_RIGHT);
}
