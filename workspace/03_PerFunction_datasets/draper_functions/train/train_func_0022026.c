st_disconnect(SearchThread *st)
{
    if (st->soc < 0) {
        if (ldap_get_option(st->ld, LDAP_OPT_DESC, (void *)&st->soc)
	    != LDAP_SUCCESS) {
	    fprintf(stderr, "T%d: failed on ldap_get_option\n", st->id);
	    return;
        }
    }
#ifdef XP_WIN
    if (closesocket(st->soc))
	fprintf(stderr, "T%d: failed to disconnect\n", st->id);
#else
    if (close(st->soc))
	fprintf(stderr, "T%d: failed to disconnect\n", st->id);
#endif
    st->soc = -1;
}
