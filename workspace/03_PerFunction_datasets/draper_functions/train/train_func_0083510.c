sc_kref_release(struct kref *kref)
{
	struct o2net_sock_container *sc = container_of(kref,
					struct o2net_sock_container, sc_kref);
	BUG_ON(timer_pending(&sc->sc_idle_timeout));

	sclog(sc, "releasing\n");

	if (sc->sc_sock) {
		sock_release(sc->sc_sock);
		sc->sc_sock = NULL;
	}

	o2nm_undepend_item(&sc->sc_node->nd_item);
	o2nm_node_put(sc->sc_node);
	sc->sc_node = NULL;

	o2net_debug_del_sc(sc);

	if (sc->sc_page)
		__free_page(sc->sc_page);
	kfree(sc);
}
