check_peer_expire ( gchar *ip, peer *p, time_t *now ) {
    g_message( "Checking peer %s for expire: %ld sec. remain",
	ip, p->expire - *now );
    if (p->expire <= *now) {
	remove_peer( p );
	return TRUE;
    } else {
	return FALSE;
    }
}
