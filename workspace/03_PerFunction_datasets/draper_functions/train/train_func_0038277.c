goal_seek_newton_polish (GoalSeekFunction f, GoalSeekFunction df,
			 GoalSeekData *data, void *user_data,
			 gnm_float x0, gnm_float y0)
{
	int iterations;
	gnm_float last_df0 = 1;
	gboolean try_newton = TRUE;
	gboolean try_square = x0 != 0 && gnm_abs (x0) < 1e10;

#ifdef DEBUG_GOAL_SEEK
	g_print ("goal_seek_newton_polish\n");
#endif

	for (iterations = 0; iterations < 20; iterations++) {
		if (try_square) {
			gnm_float x1 = x0 * gnm_abs (x0);
			gnm_float y1, r;
			GoalSeekStatus status = f (x1, &y1, user_data);
			if (status != GOAL_SEEK_OK)
				goto nomore_square;

			if (update_data (x1, y1, data))
				return GOAL_SEEK_OK;

			r = gnm_abs (y1 / y0);
			if (r >= 1)
				goto nomore_square;

			x0 = x1;
#ifdef DEBUG_GOAL_SEEK
			g_print ("polish square: x0=%.20" GNM_FORMAT_g "\n",
				 x0);
#endif
			if (r > 0.5)
				goto nomore_square;

			continue;

		nomore_square:
			try_square = FALSE;
		}

		if (try_newton) {
			gnm_float df0, r, x1, y1;
			GoalSeekStatus status = df
				? df (x0, &df0, user_data)
				: fake_df (f, x0, &df0, gnm_abs (x0) / 1e6, data, user_data);
			if (status != GOAL_SEEK_OK || df0 == 0)
				df0 = last_df0;
			else
				last_df0 = df0;

			x1 = x0 - y0 / df0;
			if (x1 < data->xmin || x1 > data->xmax)
				goto nomore_newton;

			status = f (x1, &y1, user_data);
			if (status != GOAL_SEEK_OK)
				goto nomore_newton;

			if (update_data (x1, y1, data))
				return GOAL_SEEK_OK;

			r = gnm_abs (y1 / y0);
			if (r >= 1)
				goto nomore_newton;

			x0 = x1;
#ifdef DEBUG_GOAL_SEEK
			g_print ("polish Newton: x0=%.20" GNM_FORMAT_g "\n",
				 x0);
#endif
			if (r > 0.5)
				goto nomore_newton;

			continue;

		nomore_newton:
			try_newton = FALSE;
		}


		break;
	}

	if (goal_seek_bisection (f, data, user_data) == GOAL_SEEK_OK)
		return GOAL_SEEK_OK;

	data->root = x0;
	data->have_root = TRUE;
	return GOAL_SEEK_OK;
}
