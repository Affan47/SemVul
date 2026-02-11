virtual_remove(struct transport *t)
{
	struct virtual_transport *v = (struct virtual_transport *)t;

	if (v->encap)
		v->encap->vtbl->remove(v->encap);
	if (v->main)
		v->main->vtbl->remove(v->main);
	if (v->link.le_prev)
		LIST_REMOVE(v, link);

	LOG_DBG((LOG_TRANSPORT, 90, "virtual_remove: removed %p", v));
	free(t);
}
