cli_hashtab_find(const struct cli_hashtable *s,const char* key,const size_t len)
{
	struct cli_element* element;
	size_t tries = 1;
	size_t idx;

	if(!s)
		return NULL;
	PROFILE_CALC_HASH(s);
	PROFILE_FIND_ELEMENT(s);
	idx = hash((const unsigned char*)key, len, s->capacity);
	element = &s->htable[idx];
	do {
		if(!element->key) {
			PROFILE_FIND_NOTFOUND(s, tries);
			return NULL;
		}
		else if(element->key != DELETED_KEY && len == element->len && (key == element->key || strncmp(key, element->key,len)==0)) {
			PROFILE_FIND_FOUND(s, tries);
			return element;
		}
		else {
			idx = (idx + tries++) & (s->capacity-1);
			element = &s->htable[idx];
		}
	} while (tries <= s->capacity);
	PROFILE_HASH_EXHAUSTED(s);
	return NULL;
}
