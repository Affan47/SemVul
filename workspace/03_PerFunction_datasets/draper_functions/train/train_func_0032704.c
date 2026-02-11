addValueToDictionary(Dictionary* dict, const char* key, DictValue* value) {
	value->key = (char*) malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(value->key, key);
	DictValue* curValue = dict->values;
	DictValue* prevValue = NULL;

	while(curValue != NULL) {
		prevValue = curValue;
		curValue = curValue->next;
	}

	value->next = NULL;
	value->prev = prevValue;

	if(prevValue == NULL)
		dict->values = value;
	else
		prevValue->next = value;
}
