vrrp_snmp_script(struct variable *vp, oid *name, size_t *length,
		 int exact, size_t *var_len, WriteMethod **write_method)
{
        static unsigned long long_ret;
	vrrp_script_t *scr;

	if ((scr = (vrrp_script_t *)snmp_header_list_table(vp, name, length, exact,
							   var_len, write_method,
							   vrrp_data->vrrp_script)) == NULL)
		return NULL;

	switch (vp->magic) {
	case VRRP_SNMP_SCRIPT_NAME:
		*var_len = strlen(scr->sname);
		return (u_char *)scr->sname;
	case VRRP_SNMP_SCRIPT_COMMAND:
		*var_len = strlen(scr->script);
		return (u_char *)scr->script;
	case VRRP_SNMP_SCRIPT_INTERVAL:
		long_ret = scr->interval / TIMER_HZ;
		return (u_char *)&long_ret;
	case VRRP_SNMP_SCRIPT_WEIGHT:
		long_ret = scr->weight;
		return (u_char *)&long_ret;
	case VRRP_SNMP_SCRIPT_RESULT:
		switch (scr->result) {
		case VRRP_SCRIPT_STATUS_INIT:
			long_ret = 1; break;
		case VRRP_SCRIPT_STATUS_INIT_GOOD:
			long_ret = 4; break;
		case VRRP_SCRIPT_STATUS_DISABLED:
			long_ret = 0; break;
		default:
			long_ret = (scr->result >= scr->rise) ? 3 : 2;
		}
		return (u_char *)&long_ret;
	case VRRP_SNMP_SCRIPT_RISE:
		long_ret = scr->rise;
		return (u_char *)&long_ret;
	case VRRP_SNMP_SCRIPT_FALL:
		long_ret = scr->fall;
		return (u_char *)&long_ret;
	default:
		break;
        }
        return NULL;
}
