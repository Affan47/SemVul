dump_ipseckey(DUMP_PARAMS)
{
	DUMP_INIT;

	if (p.style->wrap) {
		DUMP_NUM8; DUMP_SPACE; WRAP_INIT;
		DUMP_GATEWAY;
		WRAP_END;
	} else {
		DUMP_NUM8; DUMP_SPACE;
		DUMP_GATEWAY;
	}

	DUMP_END;
}
