chancleanup() {

	unsigned int i;

	TRACE(("enter chancleanup"))
	for (i = 0; i < ses.chansize; i++) {
		if (ses.channels[i] != NULL) {
			TRACE(("channel %d closing", i))
			remove_channel(ses.channels[i]);
		}
	}
	m_free(ses.channels);
	TRACE(("leave chancleanup"))
}
