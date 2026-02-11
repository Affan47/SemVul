fwrr_get_next_server(struct proxy *p, struct server *srvtoavoid)
{
	struct server *srv, *full, *avoided;
	struct fwrr_group *grp;
	int switched;

	if (p->srv_act)
		grp = &p->lbprm.fwrr.act;
	else if (p->lbprm.fbck)
		return p->lbprm.fbck;
	else if (p->srv_bck)
		grp = &p->lbprm.fwrr.bck;
	else
		return NULL;

	switched = 0;
	avoided = NULL;
	full = NULL;
	while (1) {


		if (!grp->curr_weight)
			grp->curr_pos = grp->curr_weight = grp->next_weight;


		while (1) {
			srv = fwrr_get_server_from_group(grp);
			if (srv)
				break;
			if (switched) {
				if (avoided) {
					srv = avoided;
					break;
				}
				goto requeue_servers;
			}
			switched = 1;
			fwrr_switch_trees(grp);

		}


		fwrr_update_position(grp, srv);
		fwrr_dequeue_srv(srv);
		grp->curr_pos++;
		if (!srv->maxconn || (!srv->nbpend && srv->served < srv_dynamic_maxconn(srv))) {

			if (srv != srvtoavoid || avoided)
				break;

			avoided = srv;
		}


		srv->next_full = full;
		full = srv;
	}


	fwrr_queue_srv(srv);

 requeue_servers:


	if (unlikely(full != NULL)) {
		if (switched) {


			do {
				if (likely(full != srv))
					fwrr_queue_by_weight(grp->init, full);
				full = full->next_full;
			} while (full);
		} else {


			do {
				if (likely(full != srv))
					fwrr_queue_srv(full);
				full = full->next_full;
			} while (full);
		}
	}
	return srv;
}
