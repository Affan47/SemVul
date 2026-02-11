ruv_is_newer (Object *sruvobj, Object *cruvobj)
{
	RUV *sruv, *cruv;
	RUVElement *sreplica, *creplica;
	int scookie, ccookie;
	int is_newer = PR_FALSE;

	if ( sruvobj == NULL ) {
		return 0;
	}
	if ( cruvobj == NULL ) {
		return 1;
	}
	sruv = (RUV *) object_get_data ( sruvobj );
	cruv = (RUV *) object_get_data ( cruvobj );

	for (sreplica = dl_get_first (sruv->elements, &scookie); sreplica;
		 sreplica = dl_get_next (sruv->elements, &scookie))
	{

		if ( sreplica->csn == NULL ) continue;

		if ( cruv->elements == NULL )
			{
			slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
			"ruv_is_newer, consumer RUV has no elements\n");
			 is_newer=PR_FALSE;
			 break;
			}

		for (creplica = dl_get_first (cruv->elements, &ccookie); creplica;
			 creplica = dl_get_next (cruv->elements, &ccookie))
		{
			if ( sreplica->rid == creplica->rid ) {
				if ( csn_compare ( sreplica->csn, creplica->csn ) > 0 ) {
					is_newer = PR_TRUE;
				}
				break;
			}
		}
		if ( creplica == NULL || is_newer ) {
			is_newer = PR_TRUE;
			break;
		}
	}

	return is_newer;
}
