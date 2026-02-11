cmp_todo (Node *a, Node *b)
{
	if (!(a->flags) && !(b->flags))
		return (strcasecmp
				(fixnullstring (node_get (a, TEXT)),
				 fixnullstring (node_get (b, TEXT))));

	if (node_get(a,"done") && !node_get(b,"done"))
		return 1;
	if (!node_get(a,"done") && node_get(b,"done"))
		return -1;

	if (node_get(a,"done") && node_get(b, "done")) {
		if (!is_done(a) && is_done(b) )
			return 1;
		if (is_done(a) && !is_done(b) )
			return -1;
	}
	return (strcasecmp
			(fixnullstring (node_get (a, TEXT)),
			 fixnullstring (node_get (b, TEXT))));
}
