pcache_chk_controls(
	Operation	*op,
	SlapReply	*rs )
{
	const char	*non = "";
	const char	*stripped = "";

	switch( op->o_pagedresults ) {
	case SLAP_CONTROL_NONCRITICAL:
		non = "non-";
		stripped = "; stripped";


	case SLAP_CONTROL_CRITICAL:
		Debug( pcache_debug, "%s: "
			"%scritical pagedResults control "
			"disabled with proxy cache%s.\n",
			op->o_log_prefix, non, stripped );

		slap_remove_control( op, rs, slap_cids.sc_pagedResults, NULL );
		break;

	default:
		rs->sr_err = SLAP_CB_CONTINUE;
		break;
	}

	return rs->sr_err;
}
