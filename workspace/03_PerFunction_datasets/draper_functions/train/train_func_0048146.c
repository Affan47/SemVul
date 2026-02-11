update_shaper_tr(struct shaper_pd_t *pd)
{
	struct time_range_pd_t *tr;

	if (!pd->ses || pd->ses->terminating)
		goto out;

	list_for_each_entry(tr, &pd->tr_list, entry) {
		if (tr->id != time_range_id)
			continue;
		pd->cur_tr = tr;
		break;
	}

	if (pd->temp_down_speed || pd->temp_up_speed)
		goto out;

	if (pd->down_speed || pd->up_speed) {
		if (pd->cur_tr && pd->down_speed == pd->cur_tr->down_speed && pd->up_speed == pd->cur_tr->up_speed)
			goto out;
		remove_limiter(pd->ses);
	}

	if (pd->cur_tr && (pd->cur_tr->down_speed || pd->cur_tr->up_speed)) {
		pd->down_speed = pd->cur_tr->down_speed;
		pd->up_speed = pd->cur_tr->up_speed;
		if (!install_limiter(pd->ses, pd->cur_tr->down_speed, pd->cur_tr->down_burst, pd->cur_tr->up_speed, pd->cur_tr->up_burst)) {
			if (conf_verbose)
				log_ppp_info2("shaper: changed shaper %i/%i (Kbit)\n", pd->cur_tr->down_speed, pd->cur_tr->up_speed);
		}
	} else {
		if (conf_verbose)
			log_ppp_info2("shaper: removed shaper\n");
	}

out:
	if (__sync_sub_and_fetch(&pd->refs, 1) == 0) {
		clear_tr_pd(pd);
		_free(pd);
	}
}
