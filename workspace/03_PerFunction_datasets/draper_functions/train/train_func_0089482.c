ppp_terminate(struct ap_session *ses, int hard)
{
	struct ppp_t *ppp = container_of(ses, typeof(*ppp), ses);
	struct layer_node_t *n;
	struct ppp_layer_data_t *d;
	int s = 0;

	if (hard) {
		destablish_ppp(ppp);
		return;
	}

	list_for_each_entry(n,&ppp->layers,entry) {
		list_for_each_entry(d,&n->items,entry) {
			if (d->starting) {
				s = 1;
				d->layer->finish(d);
			}
		}
	}
	if (s)
		return;

	destablish_ppp(ppp);
}
