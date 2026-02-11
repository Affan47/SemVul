acl__reset_cached_result (struct acl_pblock *aclpb )
{

	int		j;

	for (j =0; j < aclpb->aclpb_last_cache_result; j++) {

		if (!( aclpb->aclpb_cache_result[j].aci_ruleType & ACI_CACHE_RESULT_PER_ENTRY))
			continue;
		aclpb->aclpb_cache_result[j].result = 0;
	}
}
