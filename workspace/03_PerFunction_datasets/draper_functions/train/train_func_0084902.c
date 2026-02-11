asn1p_ref_name2lextype(char *name) {
	enum asn1p_ref_lex_type_e lex_type;
	int has_lowercase = 0;

	if(*name == '&') {
		if(name[1] >= 'A' && name[1] <= 'Z') {
			lex_type = RLT_AmpUppercase;
		} else {
			lex_type = RLT_Amplowercase;
		}
	} else if(*name >= 'A' && *name <= 'Z') {
		char *p;

		for(p = name; *p; p++) {
			if(*p >= 'a' && *p <= 'z') {
				has_lowercase = 1;
				break;
			}
		}

		if(has_lowercase) {
			lex_type = RLT_Uppercase;
		} else {
			lex_type = RLT_CAPITALS;
		}
	} else if(*name == '@') {
		if(name[1] == '.')
			lex_type = RLT_AtDotlowercase;
		else
			lex_type = RLT_Atlowercase;
	} else {
		lex_type = RLT_lowercase;
	}

	return lex_type;
}
