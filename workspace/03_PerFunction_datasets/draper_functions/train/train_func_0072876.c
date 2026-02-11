relation_needs_vacanalyze(Oid relid,
						  Form_pg_autovacuum avForm,
						  Form_pg_class classForm,
						  PgStat_StatTabEntry *tabentry,

						  bool *dovacuum,
						  bool *doanalyze,
						  bool *wraparound)
{
	bool		force_vacuum;
	float4		reltuples;


	int			vac_base_thresh,
				anl_base_thresh;
	float4		vac_scale_factor,
				anl_scale_factor;


	float4		vacthresh,
				anlthresh;


	float4		vactuples,
				anltuples;


	int			freeze_max_age;
	TransactionId xidForceLimit;

	AssertArg(classForm != NULL);
	AssertArg(OidIsValid(relid));


	if (avForm != NULL)
	{
		vac_scale_factor = (avForm->vac_scale_factor >= 0) ?
			avForm->vac_scale_factor : autovacuum_vac_scale;
		vac_base_thresh = (avForm->vac_base_thresh >= 0) ?
			avForm->vac_base_thresh : autovacuum_vac_thresh;

		anl_scale_factor = (avForm->anl_scale_factor >= 0) ?
			avForm->anl_scale_factor : autovacuum_anl_scale;
		anl_base_thresh = (avForm->anl_base_thresh >= 0) ?
			avForm->anl_base_thresh : autovacuum_anl_thresh;

		freeze_max_age = (avForm->freeze_max_age >= 0) ?
			Min(avForm->freeze_max_age, autovacuum_freeze_max_age) :
			autovacuum_freeze_max_age;
	}
	else
	{
		vac_scale_factor = autovacuum_vac_scale;
		vac_base_thresh = autovacuum_vac_thresh;

		anl_scale_factor = autovacuum_anl_scale;
		anl_base_thresh = autovacuum_anl_thresh;

		freeze_max_age = autovacuum_freeze_max_age;
	}


	xidForceLimit = recentXid - freeze_max_age;
	if (xidForceLimit < FirstNormalTransactionId)
		xidForceLimit -= FirstNormalTransactionId;
	force_vacuum = (TransactionIdIsNormal(classForm->relfrozenxid) &&
					TransactionIdPrecedes(classForm->relfrozenxid,
										  xidForceLimit));
	*wraparound = force_vacuum;


	if (avForm && !avForm->enabled && !force_vacuum)
	{
		*doanalyze = false;
		*dovacuum = false;
		return;
	}

	if (PointerIsValid(tabentry))
	{
		reltuples = classForm->reltuples;
		vactuples = tabentry->n_dead_tuples;
		anltuples = tabentry->n_live_tuples + tabentry->n_dead_tuples -
			tabentry->last_anl_tuples;

		vacthresh = (float4) vac_base_thresh + vac_scale_factor * reltuples;
		anlthresh = (float4) anl_base_thresh + anl_scale_factor * reltuples;


		elog(DEBUG3, "%s: vac: %.0f (threshold %.0f), anl: %.0f (threshold %.0f)",
			 NameStr(classForm->relname),
			 vactuples, vacthresh, anltuples, anlthresh);


		*dovacuum = force_vacuum || (vactuples > vacthresh);
		*doanalyze = (anltuples > anlthresh);
	}
	else
	{


		*dovacuum = force_vacuum;
		*doanalyze = false;
	}


	if (relid == StatisticRelationId)
		*doanalyze = false;
}
