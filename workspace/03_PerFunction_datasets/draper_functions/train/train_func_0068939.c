nvpair_parse(struct nvpair *n, const char *data)
{
	char *text = xxstrdup(data);
	char *name, *value;

	name = strtok(text, " ");
	while(name) {
		value = strtok(0, "\n");
		if(value) {
			nvpair_insert_string(n, name, value);
		} else {
			break;
		}
		name = strtok(0, " ");
	}

	free(text);
}
