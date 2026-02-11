createRoot(char* xml) {
	Tag* tag;
	Dictionary* dict;

	xml = strstr(xml, "<dict>");
	tag = getNextTag(&xml);
	dict = malloc(sizeof(Dictionary));
	if(dict == NULL) {
		return NULL;
	}
	dict->dValue.next = NULL;
	dict->dValue.key = malloc(sizeof("root"));
	strcpy(dict->dValue.key, "root");
	dict->values = NULL;
	createDictionary(dict, tag->xml);
	releaseTag(tag);
	return dict;
}
