od_draw_frame_end_full (GsfXMLIn *xin, gboolean absolute_distance, char const *control_name)
{
	OOParseState *state = (OOParseState *)xin->user_state;

	if (state->chart.so != NULL) {


		object_offset_t *ob_off = g_new (object_offset_t, 1);

		sheet_object_set_anchor (state->chart.so, &state->chart.anchor);
		ob_off->so = state->chart.so;
		ob_off->absolute_distance = absolute_distance;
		ob_off->z_index = state->chart.z_index;
		ob_off->control = g_strdup (control_name);
		ob_off->frame_offset[0] = state->chart.frame_offset[0];
		ob_off->frame_offset[1] = state->chart.frame_offset[1];
		ob_off->frame_offset[2] = state->chart.frame_offset[2];
		ob_off->frame_offset[3] = state->chart.frame_offset[3];
		state->chart_list = g_slist_prepend ( state->chart_list, ob_off);

		state->chart.so = NULL;
	}
}
