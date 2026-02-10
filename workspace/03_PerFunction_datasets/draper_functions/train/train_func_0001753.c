__connman_service_ipconfig_indicate_state(struct connman_service *service,
					enum connman_service_state new_state,
					enum connman_ipconfig_type type)
{
	struct connman_ipconfig *ipconfig = NULL;
	enum connman_service_state old_state;
	int ret;

	if (service == NULL)
		return -EINVAL;

	if (type == CONNMAN_IPCONFIG_TYPE_IPV4) {
		old_state = service->state_ipv4;
		ipconfig = service->ipconfig_ipv4;
	} else if (type == CONNMAN_IPCONFIG_TYPE_IPV6) {
		old_state = service->state_ipv6;
		ipconfig = service->ipconfig_ipv6;
	}

	if (ipconfig == NULL)
		return -EINVAL;


	if (old_state == new_state)
		return -EALREADY;

	DBG("service %p (%s) state %d (%s) type %d (%s)",
		service, service ? service->identifier : NULL,
		new_state, state2string(new_state),
		type, __connman_ipconfig_type2string(type));

	switch (new_state) {
	case CONNMAN_SERVICE_STATE_UNKNOWN:
	case CONNMAN_SERVICE_STATE_IDLE:
		if (service->state == CONNMAN_SERVICE_STATE_FAILURE)
			return -EINVAL;
		break;
	case CONNMAN_SERVICE_STATE_ASSOCIATION:
		break;
	case CONNMAN_SERVICE_STATE_CONFIGURATION:
		__connman_ipconfig_enable(ipconfig);
		break;
	case CONNMAN_SERVICE_STATE_READY:
		update_nameservers(service);

		if (type == CONNMAN_IPCONFIG_TYPE_IPV4) {
			check_proxy_setup(service);
			service_rp_filter(service, TRUE);
		} else {
			service->online_check_count = 1;
			__connman_wispr_start(service, type);
		}
		break;
	case CONNMAN_SERVICE_STATE_ONLINE:
		break;
	case CONNMAN_SERVICE_STATE_DISCONNECT:
		if (service->state == CONNMAN_SERVICE_STATE_IDLE)
			return -EINVAL;

		if (type == CONNMAN_IPCONFIG_TYPE_IPV4)
			service_rp_filter(service, FALSE);

		break;
	case CONNMAN_SERVICE_STATE_FAILURE:
		break;
	}


	if (type == CONNMAN_IPCONFIG_TYPE_IPV4)
		service->state_ipv4 = new_state;
	else if (type == CONNMAN_IPCONFIG_TYPE_IPV6)
		service->state_ipv6 = new_state;

	ret = service_indicate_state(service);


	if (type == CONNMAN_IPCONFIG_TYPE_IPV4) {
		enum connman_ipconfig_method method;
		method = __connman_ipconfig_get_method(service->ipconfig_ipv4);
		if (method == CONNMAN_IPCONFIG_METHOD_OFF ||
				method == CONNMAN_IPCONFIG_METHOD_UNKNOWN) {
			service->state_ipv4 = CONNMAN_SERVICE_STATE_IDLE;
			ret = service_indicate_state(service);
		}

	} else if (type == CONNMAN_IPCONFIG_TYPE_IPV6) {
		enum connman_ipconfig_method method;
		method = __connman_ipconfig_get_method(service->ipconfig_ipv6);
		if (method == CONNMAN_IPCONFIG_METHOD_OFF ||
				method == CONNMAN_IPCONFIG_METHOD_UNKNOWN) {
			service->state_ipv6 = CONNMAN_SERVICE_STATE_IDLE;
			ret = service_indicate_state(service);
		}
	}

	return ret;
}
