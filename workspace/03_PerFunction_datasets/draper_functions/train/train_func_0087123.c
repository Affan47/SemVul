html_tag_arg_free(tag_arguments_t *tags)
{
	int i;

	for (i=0; i < tags->count; i++) {
		free(tags->tag[i]);
		if (tags->value[i]) {
			free(tags->value[i]);
		}
		if(tags->contents)
			if (tags->contents[i])
				free(tags->contents[i]);
	}
	if (tags->tag) {
		free(tags->tag);
	}
	if (tags->value) {
		free(tags->value);
	}
	if(tags->contents)
		free(tags->contents);
	tags->contents = NULL;
	tags->tag = tags->value = NULL;
	tags->count = 0;
}
