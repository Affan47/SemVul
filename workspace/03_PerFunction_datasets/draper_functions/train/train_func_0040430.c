lrm_concat(const char *prefix, const char *suffix, char join)
{
	int len = 2;
	char *new_str = NULL;
	len += safe_len(prefix);
	len += safe_len(suffix);

	new_str = malloc(sizeof(char)*len);
	if (NULL == new_str) {
		lrmd_log(LOG_ERR,"%s:%d: malloc failed"
			 , __FUNCTION__, __LINE__);
		return NULL;
	}

	memset(new_str, 0, len);
	sprintf(new_str, "%s%c%s", prefix?prefix:"", join, suffix?suffix:"");
	new_str[len-1] = 0;
	return new_str;
}
