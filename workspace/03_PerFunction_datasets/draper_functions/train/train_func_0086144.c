validate_subdomain(const struct regex_list *regex, const struct pre_fixup_info *pre_fixup, const char *buffer, size_t buffer_len, char *real_url, size_t real_len, char *orig_real_url)
{
	char c;
	size_t match_len;

	if(!regex || !regex->pattern)
		return 0;
	match_len = strlen(regex->pattern);
	if(((c=get_char_at_pos_with_skip(pre_fixup,buffer,buffer_len+1))==' ' || c=='\0' || c=='/' || c=='?') &&
			(match_len == buffer_len ||
			 (match_len < buffer_len &&
			  ((c=get_char_at_pos_with_skip(pre_fixup,buffer,buffer_len-match_len))=='.' || (c==' ')) )
			 )) {

		if(match_len > 0) match_len--;
		cli_dbgmsg("Got a match: %s with %s\n", buffer, regex->pattern);
		cli_dbgmsg("Before inserting .: %s\n", orig_real_url);
		if(real_len >= match_len + 1) {
			const size_t pos = real_len - match_len - 1;
			if(real_url[pos] != '.') {


				size_t orig_real_len = strlen(orig_real_url);
				cli_dbgmsg("No dot here:%s\n",real_url+pos);
				real_url = orig_real_url;
				memmove(real_url, real_url+1, orig_real_len-match_len-1);
				real_url[orig_real_len-match_len-1]='.';
				cli_dbgmsg("After inserting .: %s\n", real_url);
			}
		}
		return 1;
	}
	cli_dbgmsg("Ignoring false match: %s with %s, mismatched character: %c\n", buffer, regex->pattern, c);
	return 0;
}
