ev_ppp_pre_up(struct ap_session *ses)
{
	int down_speed, down_burst;
	int up_speed, up_burst;
	struct shaper_pd_t *pd = find_pd(ses, 1);

	if (!pd)
		return;

	if (temp_down_speed || temp_up_speed) {
		pd->temp_down_speed = temp_down_speed;
		pd->temp_up_speed = temp_up_speed;
		pd->down_speed = temp_down_speed;
		pd->up_speed = temp_up_speed;
		down_speed = temp_down_speed;
		up_speed = temp_up_speed;
		down_burst = 0;
		up_burst = 0;
	} else {
		if (!pd->cur_tr)
			return;
		pd->down_speed = pd->cur_tr->down_speed;
		pd->up_speed = pd->cur_tr->up_speed;
		down_speed = pd->cur_tr->down_speed;
		up_speed = pd->cur_tr->up_speed;
		down_burst = pd->cur_tr->down_burst;
		up_burst = pd->cur_tr->up_burst;
	}

	if (down_speed > 0 && up_speed > 0) {
		if (!install_limiter(ses, down_speed, down_burst, up_speed, up_burst)) {
			if (conf_verbose)
				log_ppp_info2("shaper: installed shaper %i/%i (Kbit)\n", down_speed, up_speed);
		}
	}
}
