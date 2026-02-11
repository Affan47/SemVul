fwlc_set_server_status_down(struct server *srv)
{
	struct proxy *p = srv->proxy;

	if (srv->state == srv->prev_state &&
	    srv->eweight == srv->prev_eweight)
		return;

	if (srv_is_usable(srv->state, srv->eweight))
		goto out_update_state;

	if (!srv_is_usable(srv->prev_state, srv->prev_eweight))

		goto out_update_backend;

	if (srv->state & SRV_BACKUP) {
		p->lbprm.tot_wbck -= srv->prev_eweight;
		p->srv_bck--;

		if (srv == p->lbprm.fbck) {


			struct server *srv2 = p->lbprm.fbck;
			do {
				srv2 = srv2->next;
			} while (srv2 &&
				 !((srv2->state & SRV_BACKUP) &&
				   srv_is_usable(srv2->state, srv2->eweight)));
			p->lbprm.fbck = srv2;
		}
	} else {
		p->lbprm.tot_wact -= srv->prev_eweight;
		p->srv_act--;
	}

	fwlc_dequeue_srv(srv);
	fwlc_remove_from_tree(srv);

out_update_backend:

	update_backend_weight(p);
 out_update_state:
	srv->prev_state = srv->state;
	srv->prev_eweight = srv->eweight;
}
