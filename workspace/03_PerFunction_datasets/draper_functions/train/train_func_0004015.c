node2path (Node *node)
{
	static char path[2048];
	int pos = 0;
	int levels = nodes_left (node);
	int cnt;

	path[pos] = '/';
	path[++pos] = 0;

	for (cnt = levels; cnt >= 0; cnt--) {
		int cnt2;
		Node *tnode = node;

		for (cnt2 = 0; cnt2 < cnt; cnt2++)
			tnode = node_left (tnode);

		strcpy (&path[pos], fixnullstring (node_get (tnode, TEXT)));
		pos = strlen (path);
		path[pos] = '/';
		path[++pos] = 0;
	}

	path[--pos] = 0;

	return (path);
}
