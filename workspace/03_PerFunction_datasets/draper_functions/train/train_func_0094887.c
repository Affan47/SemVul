vrrp_snmp_syncgroup(struct variable *vp, oid *name, size_t *length,
		 int exact, size_t *var_len, WriteMethod **write_method)
{
        static unsigned long long_ret;
	vrrp_sgroup_t *group;

	if ((group = (vrrp_sgroup_t *)
	     snmp_header_list_table(vp, name, length, exact,
				    var_len, write_method,
				    vrrp_data->vrrp_sync_group)) == NULL)
		return NULL;

	switch (vp->magic) {
	case VRRP_SNMP_SYNCGROUP_NAME:
		*var_len = strlen(group->gname);
		return (u_char *)group->gname;
	case VRRP_SNMP_SYNCGROUP_STATE:
		long_ret = vrrp_snmp_state(group->state);
		return (u_char *)&long_ret;
	case VRRP_SNMP_SYNCGROUP_SMTPALERT:
		long_ret = group->smtp_alert?1:2;
		return (u_char *)&long_ret;
	case VRRP_SNMP_SYNCGROUP_NOTIFYEXEC:
		long_ret = group->notify_exec?1:2;
		return (u_char *)&long_ret;
	case VRRP_SNMP_SYNCGROUP_SCRIPTMASTER:
		if (group->script_master) {
			*var_len = strlen(group->script_master);
			return (u_char *)group->script_master;
		}
		break;
	case VRRP_SNMP_SYNCGROUP_SCRIPTBACKUP:
		if (group->script_backup) {
			*var_len = strlen(group->script_backup);
			return (u_char *)group->script_backup;
		}
		break;
	case VRRP_SNMP_SYNCGROUP_SCRIPTFAULT:
		if (group->script_fault) {
			*var_len = strlen(group->script_fault);
			return (u_char *)group->script_fault;
		}
		break;
	case VRRP_SNMP_SYNCGROUP_SCRIPT:
		if (group->script) {
			*var_len = strlen(group->script);
			return (u_char *)group->script;
		}
		break;
	default:
		return NULL;
        }


	if (!exact && (name[*length-1] < MAX_SUBID))
		return vrrp_snmp_syncgroup(vp, name, length,
					   exact, var_len, write_method);
        return NULL;
}
