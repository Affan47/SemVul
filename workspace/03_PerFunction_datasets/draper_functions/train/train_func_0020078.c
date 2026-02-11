trie_longest_prefix(trie_t * t, const char * full_key, char * buff) {
	trie_node_t * n1;
	trie_node_t * n2;
	const char * c;
	char * part_key;
	char lastc;
	int num_chars = 0;
	int count = 0;
	int i = 0;

	assert(t);

	buff[0] = 0;

	part_key = malloc(strlen(full_key) + 1);
	part_key[0] = 0;

	n1 = t->root;

	lastc = 0;
	c = full_key;

	while (*c) {
		if (lastc == t->delim && *c == t->delim ) {
			lastc = *c;
			c++;
			count++;
		} else {
			if (*c == t->delim && num_chars != 0) {
				part_key[i] = 0;
				n2 = trie_find_child(n1, part_key);
				if ( !n2 ) {
					free(part_key);
					return n1;
				} else {
					n1 = n2;
					memcpy(buff, full_key, count * sizeof(char));
					buff[count+1] = 0;
					i = 0;
				}
			}
			if ( *c != t->delim) {
				part_key[i] = *c;
				i++;
			}
			count++;
			lastc = *c;
			c++;
			num_chars++;
		}
	}


	if ( (c = rindex(full_key, t->delim)) == NULL) {
		if ((n2 = trie_find_child(t->root, full_key)) != NULL ) {
			strcpy(buff, full_key);
			n1 = n2;
		} else {
			n1 = t->root;
		}
	} else {
		strcpy(part_key, c+1);
		n2 = trie_find_child(n1, part_key);
		if ( n2 ) {
			strcpy(buff, full_key);
			n1 = n2;
		}
	}

	free(part_key);
	return n1;
}
