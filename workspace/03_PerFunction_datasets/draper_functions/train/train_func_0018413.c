undefer(int ticket) {
	if (ticket != UNREGISTERED) {
		Defer *defer;
		assert(ticket >= 0);
		assert(defcount > 0);
		defer = &deftab[--defcount];
		assert(ticket == defcount);
		unregisterfd(&defer->realfd);
		if (defer->realfd != -1)
			close(defer->realfd);
	}
}
