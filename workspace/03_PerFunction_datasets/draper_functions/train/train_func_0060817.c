hex_document_find_forward(HexDocument *doc, guint start, guchar *what,
						  gint len, guint *found)
{
	guint pos;

	pos = start;
	while(pos < doc->file_size) {
		if(hex_document_compare_data(doc, what, pos, len) == 0) {
			*found = pos;
			return TRUE;
		}
		pos++;
	}

	return FALSE;
}
