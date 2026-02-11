segment_remove (GtkSourceContextEngine *ce,
		Segment                *segment)
{
	if (segment->next != NULL)
		segment->next->prev = segment->prev;
	else
		segment->parent->last_child = segment->prev;

	if (segment->prev != NULL)
		segment->prev->next = segment->next;
	else
		segment->parent->children = segment->next;


	if (ce->priv->hint == segment)
	{
		if (segment->next != NULL)
			ce->priv->hint = segment->next;
		else if (segment->prev != NULL)
			ce->priv->hint = segment->prev;
		else
			ce->priv->hint = segment->parent;
	}


        if (ce->priv->hint2 == segment)
        {
                if (segment->next != NULL)
                        ce->priv->hint2 = segment->next;
                else if (segment->prev != NULL)
                        ce->priv->hint2 = segment->prev;
                else
                        ce->priv->hint2 = segment->parent;
        }

	segment_destroy (ce, segment);
}
