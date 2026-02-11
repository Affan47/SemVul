update_data (gnm_float x, gnm_float y, GoalSeekData *data)
{
	if (!gnm_finite (y))
		return FALSE;

	if (y > 0) {
		if (data->havexpos) {
			if (data->havexneg) {


				if (gnm_abs (x - data->xneg) < gnm_abs (data->xpos - data->xneg)) {
					data->xpos = x;
					data->ypos = y;
				}
			} else if (y < data->ypos) {

				data->xpos = x;
				data->ypos = y;
			}
		} else {
			data->xpos = x;
			data->ypos = y;
			data->havexpos = TRUE;
		}
		return FALSE;
	} else if (y < 0) {
		if (data->havexneg) {
			if (data->havexpos) {


				if (gnm_abs (x - data->xpos) < gnm_abs (data->xpos - data->xneg)) {
					data->xneg = x;
					data->yneg = y;
				}
			} else if (-y < -data->yneg) {

				data->xneg = x;
				data->yneg = y;
			}

		} else {
			data->xneg = x;
			data->yneg = y;
			data->havexneg = TRUE;
		}
		return FALSE;
	} else {

		data->have_root = TRUE;
		data->root = x;
#ifdef DEBUG_GOAL_SEEK
		g_print ("update_data: got root %.20" GNM_FORMAT_g "\n", x);
#endif
		return TRUE;
	}
}
