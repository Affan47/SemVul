parse_lease_time (cfile, timep)
	struct parse *cfile;
	TIME *timep;
{
	const char *val;
	enum dhcp_token token;
	u_int32_t num;

	token = next_token (&val, (unsigned *)0, cfile);
	if (token != NUMBER) {
		parse_warn (cfile, "Expecting numeric lease time");
		skip_to_semi (cfile);
		return;
	}
	convert_num(cfile, (unsigned char *)&num, val, 10, 32);

	*timep = ntohl(num);

	parse_semi (cfile);
}
