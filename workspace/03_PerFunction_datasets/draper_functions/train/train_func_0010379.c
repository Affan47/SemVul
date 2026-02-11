isns_policy_validate_entity(const isns_policy_t *policy,
			const char *eid)
{
	int	rv = 0, eidlen;


	if (policy->ip_node_types & ISNS_ISCSI_CONTROL_MASK)
		goto accept;


	if (IS_ANON_POLICY(policy))
		goto reject;


	if (policy->ip_entity == NULL)
		goto reject;

	eidlen = strlen(policy->ip_entity);
	if (strncasecmp(policy->ip_entity, eid, eidlen)
	 && (eid[eidlen] == ':' || eid[eidlen] == '\0'))
		goto reject;

accept:	rv = 1;

reject:
	isns_debug_auth(":: policy %s entity ID %s %s\n",
			policy->ip_name, eid,
			rv? "permitted" : "DENIED");
	return rv;
}
