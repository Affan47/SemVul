html_tag_arg_value(tag_arguments_t *tags, const char *tag)
{
	int i;

	for (i=0; i < tags->count; i++) {
		if (strcmp((const char*)tags->tag[i], tag) == 0) {
			return (char*)tags->value[i];
		}
	}
	return NULL;
}
