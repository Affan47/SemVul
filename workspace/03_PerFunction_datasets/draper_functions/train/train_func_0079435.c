start_confirm(gpointer user_data)
{
	struct connman_dhcpv6 *dhcp = user_data;


	dhcp->RT = CNF_TIMEOUT * (1 + get_random());

	DBG("confirm initial RT timeout %d msec", dhcp->RT);

	dhcp->timeout = g_timeout_add(dhcp->RT, timeout_confirm, dhcp);
	dhcp->MRD = g_timeout_add(CNF_MAX_RD, timeout_max_confirm, dhcp);

	dhcpv6_confirm(dhcp);

	return FALSE;
}
