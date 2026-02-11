rndr_tablecell(struct buf *ob, const struct buf *text, int flags, void *opaque)
{
	if (flags & MKD_TABLE_HEADER) {
		BUFPUTSL(ob, "<th");
	} else {
		BUFPUTSL(ob, "<td");
	}

	switch (flags & MKD_TABLE_ALIGNMASK) {
	case MKD_TABLE_ALIGN_CENTER:
		BUFPUTSL(ob, " align=\"center\">");
		break;

	case MKD_TABLE_ALIGN_L:
		BUFPUTSL(ob, " align=\"left\">");
		break;

	case MKD_TABLE_ALIGN_R:
		BUFPUTSL(ob, " align=\"right\">");
		break;

	default:
		BUFPUTSL(ob, ">");
	}

	if (text)
		bufput(ob, text->data, text->size);

	if (flags & MKD_TABLE_HEADER) {
		BUFPUTSL(ob, "</th>\n");
	} else {
		BUFPUTSL(ob, "</td>\n");
	}
}
