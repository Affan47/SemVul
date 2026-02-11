map_get_server_rr(struct proxy *px, struct server *srvtoavoid)
{
	int newidx, avoididx;
	struct server *srv, *avoided;

	if (px->lbprm.tot_weight == 0)
		return NULL;

	if (px->lbprm.map.state & LB_MAP_RECALC)
		recalc_server_map(px);

	if (px->lbprm.map.rr_idx < 0 || px->lbprm.map.rr_idx >= px->lbprm.tot_weight)
		px->lbprm.map.rr_idx = 0;
	newidx = px->lbprm.map.rr_idx;

	avoided = NULL;
	avoididx = 0;
	do {
		srv = px->lbprm.map.srv[newidx++];
		if (!srv->maxconn || srv->cur_sess < srv_dynamic_maxconn(srv)) {

			if (srv != srvtoavoid) {
				px->lbprm.map.rr_idx = newidx;
				return srv;
			}

			avoided = srv;
			avoididx = newidx;
		}
		if (newidx == px->lbprm.tot_weight)
			newidx = 0;
	} while (newidx != px->lbprm.map.rr_idx);

	if (avoided)
		px->lbprm.map.rr_idx = avoididx;


	return avoided;
}
