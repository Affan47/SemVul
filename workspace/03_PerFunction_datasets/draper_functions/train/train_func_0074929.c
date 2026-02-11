acl__scan_match_handles ( Acl_PBlock *aclpb, int type)
{


	int				matched = 0;
	aci_t			*aci = NULL;
	int				index;
	PRUint32		cookie;
	aclEvalContext	*c_evalContext = NULL;

	if (type  == ACLPB_EVALCONTEXT_PREV ) {
		c_evalContext = &aclpb->aclpb_prev_entryEval_context;
	} else if ( type == ACLPB_EVALCONTEXT_ACLCB ){
		c_evalContext = &aclpb->aclpb_prev_opEval_context;
	} else {
		return ACL_ERR;
	}


	if ( !c_evalContext->acle_numof_tmatched_handles )
		return ACL_ERR;

	aclpb->aclpb_stat_acllist_scanned++;
	aci = acllist_get_first_aci ( aclpb, &cookie );

	while ( aci ) {
		index = aci->aci_index;
		if (acl__resource_match_aci(aclpb, aci, 1 , NULL )) {
			int	j;
			int	s_matched = matched;


			for (j=0; j < c_evalContext->acle_numof_tmatched_handles ; j++ ) {
				if ( c_evalContext->acle_handles_matched_target[j]  > index )

					break;
				else if ( index == c_evalContext->acle_handles_matched_target[j] ) {
					int		jj;
					matched++;


					if ( aci->aci_ruleType & ACI_ATTR_RULES ) {
						slapi_log_error (  SLAPI_LOG_ACL, plugin_name,
							"Found an attr Rule [Name:%s Index:%d\n", aci->aclName,
							aci->aci_index );
						for ( jj =0; jj < c_evalContext->acle_numof_attrs; jj++ ) {
							AclAttrEval     *a_eval = &c_evalContext->acle_attrEval[jj];
							if ( a_eval->attrEval_r_aciIndex == aci->aci_index )
								a_eval->attrEval_r_status = ACL_ATTREVAL_RECOMPUTE;
							if ( a_eval->attrEval_s_aciIndex == aci->aci_index )
								a_eval->attrEval_s_status = ACL_ATTREVAL_RECOMPUTE;
						}
					}
					break;
				}
			}
			if ( s_matched == matched ) return ACL_ERR;
		}
		aci = acllist_get_next_aci ( aclpb, aci, &cookie );
	}
	if ( matched == c_evalContext->acle_numof_tmatched_handles )
		return 0;

	return ACL_ERR;
}
