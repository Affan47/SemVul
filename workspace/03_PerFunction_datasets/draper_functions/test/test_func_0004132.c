_clear_rotation_behaviours(GList *covers, gint current_index) {

    for (gint i = 0; i < g_list_length(covers); ++i) {
        ClarityCover *ccover = g_list_nth_data(covers, i);
        clutter_actor_set_easing_duration (CLUTTER_ACTOR(ccover), 0);


        gint index = i - current_index;
        if (index >= 1)
            clutter_actor_set_rotation_angle(CLUTTER_ACTOR(ccover), CLUTTER_Y_AXIS, MIRROR_ANGLE_CW);
        else if (index == 0)
            clutter_actor_set_rotation_angle(CLUTTER_ACTOR(ccover), CLUTTER_Y_AXIS, 0);
        else
            clutter_actor_set_rotation_angle(CLUTTER_ACTOR(ccover), CLUTTER_Y_AXIS, ANGLE_CCW);
    }
}
