kdbDelTrie(Trie *trie, CloseMapper close_backend)
{
	int i;
	if (trie==NULL) return 0;
	for (i=0;i<MAX_UCHAR;i++) {
		if (trie->text[i]!=NULL) {
			kdbDelTrie(trie->childs[i],close_backend);
			if (trie->value[i])
				close_backend(trie->value[i]);
			free(trie->text[i]);
		}
	}
	if (trie->empty_value)
		close_backend(trie->empty_value);
	free(trie);
	return 0;
}
