__aclg__delete_userGroup ( aclUserGroup *u_group )
{

	aclUserGroup		*next_group, *prev_group;
	int			i;

	if ( !u_group ) return;

	prev_group = u_group->aclug_prev;
	next_group = u_group->aclug_next;


	slapi_log_error( SLAPI_LOG_ACL, plugin_name, "DEALLOCATING GROUP FOR:%s\n", u_group->aclug_ndn );

	slapi_ch_free ( (void **) &u_group->aclug_ndn );

	PR_DestroyLock(u_group->aclug_refcnt_mutex);


	for (i=0; i < u_group->aclug_numof_member_group; i++ )
		slapi_ch_free ( (void **) &u_group->aclug_member_groups[i] );
	slapi_ch_free ( (void **) &u_group->aclug_member_groups );


	for (i=0; i < u_group->aclug_numof_notmember_group; i++ )
		slapi_ch_free ( (void **) &u_group->aclug_notmember_groups[i] );
	slapi_ch_free ( (void **) &u_group->aclug_notmember_groups );

	slapi_ch_free ( (void **) &u_group );

	if ( prev_group == NULL && next_group == NULL ) {
		aclUserGroups->aclg_first = NULL;
		aclUserGroups->aclg_last = NULL;
	} else if ( prev_group == NULL ) {
		next_group->aclug_prev = NULL;
		aclUserGroups->aclg_first = next_group;
	} else {
		prev_group->aclug_next = next_group;
		if ( next_group )
			next_group->aclug_prev = prev_group;
		else
			aclUserGroups->aclg_last = prev_group;
	}
	aclUserGroups->aclg_num_userGroups--;
}
