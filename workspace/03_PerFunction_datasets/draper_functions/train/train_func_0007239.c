vrrp_send_update(vrrp_t * vrrp, ip_address_t * ipaddress, int idx)
{
	char *msg;
	char addr_str[41];

	if (!IP_IS6(ipaddress)) {
		msg = "gratuitous ARPs";
		inet_ntop(AF_INET, &ipaddress->u.sin.sin_addr, addr_str, 41);
		send_gratuitous_arp(ipaddress);
	} else {
		msg = "Unsolicited Neighbour Adverts";
		inet_ntop(AF_INET6, &ipaddress->u.sin6_addr, addr_str, 41);
		ndisc_send_unsolicited_na(ipaddress);
	}

	if (0 == idx && debug & 32) {
		log_message(LOG_INFO, "VRRP_Instance(%s) Sending %s on %s for %s",
			    vrrp->iname, msg, IF_NAME(ipaddress->ifp), addr_str);
	}
}
