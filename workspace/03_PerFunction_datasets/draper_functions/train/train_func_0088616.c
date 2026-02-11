dump_dnskey(DUMP_PARAMS)
{
	DUMP_INIT;

	if (p.style->wrap) {
		char info[512] = "";
		dnskey_info(in, in_len, info, sizeof(info));

		DUMP_NUM16; DUMP_SPACE;
		DUMP_NUM8;  DUMP_SPACE;
		DUMP_NUM8;  DUMP_SPACE; WRAP_INIT;
		DUMP_BASE64;
		WRAP_END; COMMENT(info);
	} else {
		DUMP_NUM16; DUMP_SPACE;
		DUMP_NUM8;  DUMP_SPACE;
		DUMP_NUM8;  DUMP_SPACE;
		DUMP_BASE64;
	}

	DUMP_END;
}
