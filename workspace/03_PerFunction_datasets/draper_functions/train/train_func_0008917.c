to_money(char *str, CS_LOCALE *locale) {
	CS_MONEY mn;
	CS_DATAFMT srcfmt, destfmt;
	CS_INT reslen;

	memset(&mn, 0, sizeof(mn));

	if (!str)
		return mn;

	memset(&srcfmt, 0, sizeof(srcfmt));
	srcfmt.datatype = CS_CHAR_TYPE;
	srcfmt.maxlength = strlen(str);
	srcfmt.format = CS_FMT_NULLTERM;
	srcfmt.locale = locale;

	memset(&destfmt, 0, sizeof(destfmt));

	destfmt.datatype = CS_MONEY_TYPE;
	destfmt.locale = locale;
	destfmt.maxlength = sizeof(CS_MONEY);
	destfmt.format = CS_FMT_UNUSED;

	if (cs_convert(context, &srcfmt, str, &destfmt, &mn, &reslen) != CS_SUCCEED)
		warn("cs_convert failed (to_money(%s))", str);

	if (reslen == CS_UNUSED)
		warn("conversion failed: to_money(%s)", str);

	return mn;
}
