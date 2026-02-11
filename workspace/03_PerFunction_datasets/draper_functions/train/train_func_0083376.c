vrrp_snmp_route(struct variable *vp, oid *name, size_t *length,
		 int exact, size_t *var_len, WriteMethod **write_method)
{
        static unsigned long long_ret;
	ip_route_t *route;
	int state = HEADER_STATE_STATIC_ROUTE;

	if ((route = (ip_route_t *)
	     vrrp_header_ar_table(vp, name, length, exact,
				  var_len, write_method,
				  &state)) == NULL)
		return NULL;

	switch (vp->magic) {
	case VRRP_SNMP_ROUTE_ADDRESSTYPE:
		long_ret = 1;
		return (u_char *)&long_ret;
	case VRRP_SNMP_ROUTE_DESTINATION:
		*var_len = 4;
		return (u_char *)&route->dst;
	case VRRP_SNMP_ROUTE_DESTINATIONMASK:
		long_ret = route->dmask;
		return (u_char *)&long_ret;
	case VRRP_SNMP_ROUTE_GATEWAY:
		*var_len = 4;
		return (u_char *)&route->gw;
	case VRRP_SNMP_ROUTE_SECONDARYGATEWAY:
		if (route->gw2) {
			*var_len = 4;
			return (u_char *)&route->gw2;
		}
		break;
	case VRRP_SNMP_ROUTE_SOURCE:
		*var_len = 4;
		return (u_char *)&route->src;
	case VRRP_SNMP_ROUTE_METRIC:
		long_ret = route->metric;
		return (u_char *)&long_ret;
	case VRRP_SNMP_ROUTE_SCOPE:
		long_ret = snmp_scope(route->scope);
		return (u_char *)&long_ret;
	case VRRP_SNMP_ROUTE_TYPE:
		if (route->blackhole)
			long_ret = 3;
		else if (route->gw2)
			long_ret = 2;
		else long_ret = 1;
		return (u_char *)&long_ret;
	case VRRP_SNMP_ROUTE_IFINDEX:
		long_ret = route->index;
		return (u_char *)&long_ret;
	case VRRP_SNMP_ROUTE_IFNAME:
		if (route->index) {
			*var_len = strlen(IF_NAME(if_get_by_ifindex(route->index)));
			return (u_char *)&IF_NAME(if_get_by_ifindex(route->index));
		}
		break;
	case VRRP_SNMP_ROUTE_ROUTINGTABLE:
		long_ret = route->table;
		return (u_char *)&long_ret;
	case VRRP_SNMP_ROUTE_ISSET:
		long_ret = (route->set)?1:2;
		return (u_char *)&long_ret;
	default:
		return NULL;
        }


	if (!exact && (name[*length-1] < MAX_SUBID))
		return vrrp_snmp_route(vp, name, length,
				       exact, var_len, write_method);
        return NULL;
}
