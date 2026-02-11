t_dns_name_fromtext(void) {
	int		line;
	int		cnt;
	int		result;
	char		*p;
	FILE		*fp;

	t_assert("dns_name_fromtext", 1, T_REQUIRED, "%s", a40);

	result = T_UNRESOLVED;
	fp = fopen("dns_name_fromtext_data", "r");
	if (fp != NULL) {
		line = 0;
		while ((p = t_fgetbs(fp)) != NULL) {

			++line;


			if ((isspace((unsigned char)*p)) || (*p == '#')) {
				(void)free(p);
				continue;
			}

			cnt = bustline(p, Tokens);
			if (cnt == 4) {


				result = test_dns_name_fromtext(Tokens[0],
								Tokens[1],
								Tokens[2],
							   atoi(Tokens[3])
								== 0 ?
								0 :
							     DNS_NAME_DOWNCASE);
			} else {
				t_info("bad format at line %d\n", line);
			}

			(void)free(p);
			t_result(result);
		}
		(void)fclose(fp);
	} else {
		t_info("Missing datafile dns_name_fromtext\n");
		t_result(result);
	}
}
