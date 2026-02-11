normalize_language(normalizer_t* normalizer, char* dst, const char* src) {

	strcpy(dst, src);

	regmatch_t groups[2];
	int matches = regexec(normalizer->language_regex, dst, (size_t)2, groups, REG_NOTBOL | REG_NOTEOL);
	if(matches == 0) {

		regmatch_t group = groups[1];
		char *sn_idx = dst + group.rm_so;
		memcpy(sn_idx, "xx-xx", 5);
	}
	else {
		return false;
	}
}
