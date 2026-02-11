re_compare(const char *s, const char *pattern)
{
	bool find_target(const char *pattern, int *pindex, int plen, std::string& target, int *star, int *plus);
	int             slen = strlen(s);
	int             plen = strlen(pattern);
	int             sindex = 0;
	int             pindex = 0;
	int             star;
	int             plus;
	bool            need_new_target = true;
	int             matches = 0;

	std::string target("");
	while (sindex < slen) {
		bool            this_matches = false;
		if (need_new_target) {
			if (!find_target(pattern, &pindex, plen, target, &star, &plus)) {
#ifdef DEBUG_RE
				printf("ran out of pattern\n");
#endif
				return false;
			}
			matches = 0;
		}

#ifdef DEBUG_RE
		printf("source[%d] = `%c'  ", sindex, s[sindex]);
		show_pattern(target.c_str(), target.size(), star, plus);
#endif
		for (unsigned int tindex = 0; tindex < target.size(); tindex++) {
			if (s[sindex] == target[tindex] || target[tindex] == '.') {
				this_matches = true;
				matches++;
				break;
			}
		}

		if (this_matches) {
			if (star || plus) {
				need_new_target = false;
			}
		} else {

			if (star) {
				need_new_target = true;
				sindex--;
			} else if (plus) {
				if (matches < 1) {
					return false;
				}
				need_new_target = true;
				sindex--;
			} else {
				return false;
			}
		}
		sindex++;
	}


	if (pindex == plen) {
		return true;
	}


	while (find_target(pattern, &pindex, plen, target, &star, &plus)) {
		if (!star) {
#ifdef DEBUG_RE
			printf(" ... still some non-* target left: `%s'\n", target.c_str());
#endif
			return false;
		}
	}

	return true;
}
