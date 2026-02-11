msn_group_mod_response(MsnAccount *ma, char *data, int len,
	void *cbdata)
{
	if (!strstr(data, "<ABGroupUpdateResponse"))
		fprintf(stderr, "Group Update failed. Response ::\n%s\n", data);
}
