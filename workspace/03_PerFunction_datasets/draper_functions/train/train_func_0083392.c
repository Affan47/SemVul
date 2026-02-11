msn_group_mod(MsnAccount *ma, MsnGroup *group, const char *groupname)
{
	char *url = strdup("https://contacts.msn.com/abservice/abservice.asmx");
	char *soap_action =
		"http://www.msn.com/webservices/AddressBook/ABGroupUpdate";

	char *grp_request = msn_soap_build_request(MSN_GROUP_MOD_REQUEST,
		ma->contact_ticket,
		group->guid,
		groupname);

	free(group->name);
	group->name = strdup(groupname);

	msn_http_request(ma, MSN_HTTP_POST, soap_action, url, grp_request,
		msn_group_mod_response, NULL, group);

	free(url);
	free(grp_request);
}
