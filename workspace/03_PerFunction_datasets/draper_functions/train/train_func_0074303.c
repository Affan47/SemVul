eb_match_word_kana_single(const char *word, const char *pattern, size_t length)
{
    int i = 0;
    unsigned char *word_p = (unsigned char *)word;
    unsigned char *pattern_p = (unsigned char *)pattern;
    unsigned char wc0, wc1, pc0, pc1;
    int result;

    LOG(("in: eb_match_word_kana_single(word=%s, pattern=%s)",
	eb_quoted_stream(word, EB_MAX_WORD_LENGTH),
	eb_quoted_stream(pattern, length)));

    for (;;) {
	if (length <= i) {
	    result = *word_p;
	    break;
	}
	if (*word_p == '\0') {
	    result = 0;
	    break;
	}
	if (length <= i + 1 || *(word_p + 1) == '\0') {
	    result = *word_p - *pattern_p;
	    break;
	}

	wc0 = *word_p;
	wc1 = *(word_p + 1);
	pc0 = *pattern_p;
	pc1 = *(pattern_p + 1);

	if ((wc0 == 0x24 || wc0 == 0x25) && (pc0 == 0x24 || pc0 == 0x25)) {
	    if (wc1 != pc1) {
		result = wc1 - pc1;
		break;
	    }
	} else {
	    if (wc0 != pc0 || wc1 != pc1) {
		result = ((wc0 << 8) + wc1) - ((pc0 << 8) + pc1);
		break;
	    }
	}
	word_p += 2;
	pattern_p += 2;
	i += 2;
    }

    LOG(("out: eb_match_word_kana_single() = %d", result));
    return result;
}
