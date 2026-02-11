set_server_up(struct server *s) {

	struct server *srv;
	struct chunk msg;
	int xferred;
	unsigned int old_state = s->state;

	if (s->state & SRV_MAINTAIN) {
		s->health = s->rise;
	}

	if (s->health == s->rise || s->tracked) {
		if (s->proxy->srv_bck == 0 && s->proxy->srv_act == 0) {
			if (s->proxy->last_change < now.tv_sec)
				s->proxy->down_time += now.tv_sec - s->proxy->last_change;
			s->proxy->last_change = now.tv_sec;
		}

		if (s->last_change < now.tv_sec)
			s->down_time += now.tv_sec - s->last_change;

		s->last_change = now.tv_sec;
		s->state |= SRV_RUNNING;
		s->state &= ~SRV_MAINTAIN;

		if (s->slowstart > 0) {
			s->state |= SRV_WARMINGUP;
			if (s->proxy->lbprm.algo & BE_LB_PROP_DYN) {


				s->eweight = s->uweight;
				if (s->proxy->lbprm.update_server_eweight)
					s->proxy->lbprm.update_server_eweight(s);
			}
			task_schedule(s->warmup, tick_add(now_ms, MS_TO_TICKS(MAX(1000, s->slowstart / 20))));
		}
		if (s->proxy->lbprm.set_server_status_up)
			s->proxy->lbprm.set_server_status_up(s);


		xferred = check_for_pending(s);

		chunk_init(&msg, trash, trashlen);

		if (old_state & SRV_MAINTAIN) {
			chunk_printf(&msg,
				"%sServer %s/%s is UP (leaving maintenance)", s->state & SRV_BACKUP ? "Backup " : "",
				s->proxy->id, s->id);
		} else {
			chunk_printf(&msg,
				"%sServer %s/%s is UP", s->state & SRV_BACKUP ? "Backup " : "",
				s->proxy->id, s->id);

			server_status_printf(&msg, s,
						((!s->tracked && !(s->proxy->options2 & PR_O2_LOGHCHKS))?SSP_O_HCHK:0),
						xferred);
		}

		Warning("%s.\n", trash);
		send_log(s->proxy, LOG_NOTICE, "%s.\n", trash);

		if (s->state & SRV_CHECKED)
			for(srv = s->tracknext; srv; srv = srv->tracknext)
				if (! (srv->state & SRV_MAINTAIN))

					set_server_up(srv);
	}

	if (s->health >= s->rise)
		s->health = s->rise + s->fall - 1;

}
