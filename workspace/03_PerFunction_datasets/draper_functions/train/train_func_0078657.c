word_in_list(const char *list, const char *word) {
	int list_len, word_len = strlen(word);
	const char *find, *end_find, *end_list;


	while(isspace(*list)) {
		list++;
	}

	while((find = strstr(list, word))) {

		if (find != list && *(find - 1) != ' ') {
			list = find;

			while(!isspace(*list) && *list != '\0') {
				list++;
			}

			while(isspace(*list)) {
				list++;
			}
			continue;
		}


		list_len = strlen(list);
		end_find = find + word_len;
		end_list = list + list_len;
		if (end_find == end_list || *end_find != ' ') {
			list = find;

			while(!isspace(*list) && *list != '\0') {
				list++;
			}

			while(isspace(*list)) {
				list++;
			}
			continue;
		}


		return 1;
	}

	return 0;
}
