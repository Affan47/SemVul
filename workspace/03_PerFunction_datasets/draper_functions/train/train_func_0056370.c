ldap_pvt_runqueue_isrunning(
	struct runqueue_s* rq,
	struct re_s* entry
)
{
	struct re_s* e;

	LDAP_STAILQ_FOREACH( e, &rq->run_list, rnext ) {
		if ( e == entry ) {
			return 1;
		}
	}
	return 0;
}
