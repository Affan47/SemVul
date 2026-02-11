ldap_pvt_runqueue_stoptask(
	struct runqueue_s* rq,
	struct re_s* entry
)
{
	LDAP_STAILQ_REMOVE( &rq->run_list, entry, re_s, rnext );
}
