parsesearch(const char *cn, const char *mail,
		       void *voidarg)
{
	struct search_info *si=(struct search_info *)voidarg;

	char	numbuf[NUMBUFSIZE];
	char	numbuf2[NUMBUFSIZE+10];

	char *cn_native;

	cn_native=libmail_u_convert_fromutf8(cn, sqwebmail_content_charset,
					     NULL);

	if (cn_native)
		cn=cn_native;

	fprintf(si->fpw, "<tr valign=\"top\"><td><input type=\"checkbox\" "
				"name=\"%s\" value=\"&lt;",
		strcat(strcpy(numbuf2, "ADDY"),
		       libmail_str_size_t(si->counter++, numbuf)));

	output_attrencoded_fp(mail, si->fpw);
	fprintf(si->fpw, "&gt;");

	output_attrencoded_fp(cn, si->fpw);

	fprintf(si->fpw, "&quot;\" /></td><td><font size=\"+1\" class=\"ldapsearch-name\">\"");

	output_attrencoded_fp(cn, si->fpw);
	fprintf(si->fpw,
		"\"</font><font size=\"+1\" class=\"ldapsearch-addr\">&lt;");
	output_attrencoded_fp(mail, si->fpw);
	fprintf(si->fpw, "&gt;</font>");
	fprintf(si->fpw, "</td></tr>\n");

	if (cn_native)
		free(cn_native);
	return 0;
}
