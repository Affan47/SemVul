delete_key_names(char **key_names, uint32_t key_names_length)
{
	uint32_t key_count = 0;
	if (key_names != NULL) {
		for (key_count = 0; key_count < key_names_length; key_count++) {
			free(key_names[key_count]);

		}
		delete[](key_names);
	}
}
