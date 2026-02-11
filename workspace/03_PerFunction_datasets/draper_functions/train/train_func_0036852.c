rad_auth_recv(struct rad_req_t *req)
{
	struct rad_packet_t *pack = req->reply;
	unsigned int dt;

	triton_timer_del(&req->timeout);

	dt = (req->reply->tv.tv_sec - req->pack->tv.tv_sec) * 1000 + (req->reply->tv.tv_nsec - req->pack->tv.tv_nsec) / 1000000;
	stat_accm_add(req->serv->stat_auth_query_1m, dt);
	stat_accm_add(req->serv->stat_auth_query_5m, dt);

	if (pack->code == CODE_ACCESS_ACCEPT) {
		if (rad_proc_attrs(req)) {
			rad_auth_finalize(req->rpd, PWDB_DENIED);
			return;
		}

		struct ev_radius_t ev = {
			.ses = req->rpd->ses,
			.request = req->pack,
			.reply = pack,
		};
		triton_event_fire(EV_RADIUS_ACCESS_ACCEPT, &ev);
	} else {
		rad_auth_finalize(req->rpd, PWDB_DENIED);
		return;
	}

	if (req->rpd->auth_ctx->recv && req->rpd->auth_ctx->recv(req)) {
		rad_auth_finalize(req->rpd, PWDB_DENIED);
		return;
	}

	req->rpd->authenticated = 1;

	rad_auth_finalize(req->rpd, PWDB_SUCCESS);
}
