erase_segments (GtkSourceContextEngine *ce,
		gint                    start,
		gint                    end,
		Segment                *hint)
{
	Segment *root = ce->priv->root_segment;
	Segment *child, *hint_prev;

	if (root->children == NULL)
		return;

	if (hint == NULL)
		hint = ce->priv->hint;

	if (hint != NULL)
		while (hint != NULL && hint->parent != ce->priv->root_segment)
			hint = hint->parent;

	if (hint == NULL)
		hint = root->children;

	hint_prev = hint->prev;

	child = hint;
	while (child != NULL)
	{
		Segment *next = child->next;

		if (child->end_at < start)
		{
			child = next;

			if (next != NULL)
				ce->priv->hint = next;

			continue;
		}

		if (child->start_at > end)
		{
			ce->priv->hint = child;
			break;
		}

		segment_erase_range_ (ce, child, start, end);
		child = next;
	}

	child = hint_prev;
	while (child != NULL)
	{
		Segment *prev = child->prev;

		if (ce->priv->hint == NULL)
			ce->priv->hint = child;

		if (child->start_at > end)
		{
			child = prev;
			continue;
		}

		if (child->end_at < start)
		{
			break;
		}

		segment_erase_range_ (ce, child, start, end);
		child = prev;
	}

	CHECK_TREE (ce);
}
