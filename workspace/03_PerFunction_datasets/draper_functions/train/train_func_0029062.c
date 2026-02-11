trie_match_free (struct _trie_match *match)
{
	struct _trie_match *next;

	while (match) {
		next = match->next;
		trie_state_free (match->state);
		g_slice_free (struct _trie_match, match);
		match = next;
	}
}
