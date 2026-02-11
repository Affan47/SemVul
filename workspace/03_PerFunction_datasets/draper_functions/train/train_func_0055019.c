authenticateAuthUserRequestRemoveIp(auth_user_request_t * auth_user_request, struct in_addr ipaddr)
{
    auth_user_ip_t *ipdata;
    auth_user_t *auth_user;
    if (!auth_user_request->auth_user)
	return;
    auth_user = auth_user_request->auth_user;
    ipdata = (auth_user_ip_t *) auth_user->ip_list.head;
    while (ipdata) {

	if (ipdata->ipaddr.s_addr == ipaddr.s_addr) {
	    authenticateAuthUserRemoveIpEntry(auth_user, ipdata);
	    return;
	}
	ipdata = (auth_user_ip_t *) ipdata->node.next;
    }

}
