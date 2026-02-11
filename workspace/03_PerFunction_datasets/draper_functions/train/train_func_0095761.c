acl_clean_aclEval_context ( aclEvalContext *clean_me, int scrub_only )
{
	int		i;


	for (i=0; i < clean_me->acle_numof_attrs; i++ ) {

		char	*a_name = clean_me->acle_attrEval[i].attrEval_name;
		if ( a_name  && !scrub_only) {
			slapi_ch_free ( (void **)  &a_name );
			clean_me->acle_attrEval[i].attrEval_name = NULL;
		}
		clean_me->acle_attrEval[i].attrEval_r_status = 0;
		clean_me->acle_attrEval[i].attrEval_s_status = 0;
		clean_me->acle_attrEval[i].attrEval_r_aciIndex = 0;
		clean_me->acle_attrEval[i].attrEval_s_aciIndex = 0;
	}

	if ( !scrub_only ) clean_me->acle_numof_attrs = 0;
	clean_me->acle_numof_tmatched_handles = 0;
}
