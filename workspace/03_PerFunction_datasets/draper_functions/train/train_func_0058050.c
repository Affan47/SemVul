merge_text_node_siblings (RtNode *tree)
{
	gboolean retval = FALSE;
	while (1) {
		if (! tree->next)
			break;
		RtNode *next = tree->next;
		if ((tree->markup == RT_MARKUP_NONE) && !tree->binary.data &&
		    (next->markup == RT_MARKUP_NONE) && !next->binary.data &&
		    ! next->child && next->text) {
			if (tree->text) {
				gchar *tmp;
				tmp = tree->text;
				tree->text = g_strconcat (tmp, next->text, NULL);
				g_free (tmp);
				g_free (next->text);
			}
			else
				tree->text = next->text;
			next->text = NULL;
			RtNode *tnode = next->next;
			next->next = NULL;
			rt_free_node (next);
			tree->next = tnode;

			retval = TRUE;
		}
		else
			break;
	}

	return retval;
}
