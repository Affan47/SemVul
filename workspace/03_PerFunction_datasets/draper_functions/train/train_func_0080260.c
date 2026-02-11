_transition_layout_animation_stop(Elm_Box_Transition *layout_data)
{
   layout_data->animation_ended = EINA_TRUE;

   if (layout_data->animator)
     {
        ecore_animator_del(layout_data->animator);
        layout_data->animator = NULL;
     }

   if (layout_data->transition_end_cb)
     layout_data->transition_end_cb(layout_data->transition_end_data);
}
