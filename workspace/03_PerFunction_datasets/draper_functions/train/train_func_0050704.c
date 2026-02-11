match_opcode_name(const char *input_name, const char *opcodelist_name, int def_match)
{
	if (opcodelist_name) {
		if (*opcodelist_name == '~') opcodelist_name++;
		char n1[32], n2[32], n3[32];
		pickname(n1, opcodelist_name, 0);
		pickname(n2, opcodelist_name, 1);
		pickname(n3, opcodelist_name, 2);
		switch (opcodelist_name[0]) {
		case '|':
		case '&':
			if (strcmp(n1, input_name)==0) return def_match;
			if (strcmp(n2, input_name)==0) return def_match;
			if (strcmp(n3, input_name)==0) return def_match;
			break;
		case '?':
			if (strcmp(n1, input_name)==0) return MATCHOPNAME_MATCH_IF_OPSIZE16;
			if (strcmp(n2, input_name)==0) return MATCHOPNAME_MATCH_IF_OPSIZE32;
			if (strcmp(n3, input_name)==0) return MATCHOPNAME_MATCH_IF_OPSIZE64;
			break;
		case '*':
			if (strcmp(n1, input_name)==0) return MATCHOPNAME_MATCH_IF_ADDRSIZE16;
			if (strcmp(n2, input_name)==0) return MATCHOPNAME_MATCH_IF_ADDRSIZE32;
			if (strcmp(n3, input_name)==0) return MATCHOPNAME_MATCH_IF_ADDRSIZE64;
			break;
		default:
			if (strcmp(opcodelist_name, input_name)==0) return def_match;
		}
	}
	return MATCHOPNAME_NOMATCH;
}
