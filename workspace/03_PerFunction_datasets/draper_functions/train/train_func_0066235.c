ldapctl_criteria_list_clear( LdapControl *ctl ) {
	cm_return_if_fail( ctl != NULL );
	mgu_free_dlist( ctl->listCriteria );
	ctl->listCriteria = NULL;
}
