extractAttributes(const char * name, const char * line, const int numberOfAttributes) {
	int sz, i, currentAttribute, start;
	char ** ret;
	u8 quote=0;
	int len = strlen(line);
	start = strlen(name);
	if (len <= start)
		return NULL;
	if (!safe_start_equals(name, line))
		return NULL;
	ret = gf_calloc((numberOfAttributes + 1 ), sizeof(char*));
	currentAttribute = 0;
	for (i = start ; i <= len ; i++) {
		if (line[i] == '\0' || (!quote && line[i] == ',')  || (line[i] == quote) ) {
			u32 spaces = 0;
			sz = 1 + i - start;
			while (line[start+spaces] == ' ') spaces++;
			ret[currentAttribute] = gf_calloc( (1+sz-spaces), sizeof(char));
			strncpy(ret[currentAttribute], &(line[start+spaces]), sz-spaces);
			currentAttribute++;
			start = i+1;
			if (start == len) {
				return ret;
			}
		}
		if ((line[i] == '\'') || (line[i] == '"'))  {
			if (quote) quote = 0;
			else quote = line[i];
		}
	}
	if (currentAttribute == 0) {
		gf_free(ret);
		return NULL;
	}
	return ret;
}
