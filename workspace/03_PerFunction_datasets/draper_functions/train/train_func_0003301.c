find_insertion_place (Segment  *segment,
		      gint      offset,
		      Segment **parent,
		      Segment **prev,
		      Segment **next,
		      Segment  *hint)
{
	g_assert (segment->start_at <= offset && segment->end_at >= offset);

	*prev = NULL;
	*next = NULL;

	if (SEGMENT_IS_INVALID (segment) || segment->children == NULL)
	{
		*parent = segment;
		return;
	}

	if (segment->start_at == offset)
	{
#ifdef ENABLE_CHECK_TREE
		g_assert (!segment->children ||
			  !SEGMENT_IS_INVALID (segment->children) ||
			  segment->children->start_at > offset);
#endif

		*parent = segment;
		*next = segment->children;

		return;
	}

	if (hint != NULL)
		while (hint != NULL && hint->parent != segment)
			hint = hint->parent;

	if (hint == NULL)
		hint = segment->children;

	if (hint->end_at < offset)
		find_insertion_place_forward_ (segment, offset, hint, parent, prev, next);
	else
		find_insertion_place_backward_ (segment, offset, hint, parent, prev, next);
}
