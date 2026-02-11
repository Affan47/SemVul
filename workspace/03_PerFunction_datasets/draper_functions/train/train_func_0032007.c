elm_box_transition_free(void *data)
{
   EINA_SAFETY_ON_NULL_RETURN(data);

   Transition_Animation_Data *tad;
   Elm_Box_Transition *box_data = data;
   if ((box_data->start.free_data) && (box_data->start.data))
     box_data->start.free_data(box_data->start.data);
   if ((box_data->end.free_data) && (box_data->end.data))
     box_data->end.free_data(box_data->end.data);
   EINA_LIST_FREE (box_data->objs, tad)
     free(tad);

   evas_object_event_callback_del
     (box_data->box, EVAS_CALLBACK_RESIZE, _transition_layout_obj_resize_cb);
   evas_object_smart_callback_del
     (box_data->box, SIG_CHILD_ADDED, _transition_layout_child_added);
   evas_object_smart_callback_del
     (box_data->box, SIG_CHILD_REMOVED, _transition_layout_child_removed);
   if (box_data->animator)
     {
        ecore_animator_del(box_data->animator);
        box_data->animator = NULL;
     }

   free(data);
}
