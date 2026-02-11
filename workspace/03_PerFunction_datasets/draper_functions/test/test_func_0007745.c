hex_document_real_undo(HexDocument *doc)
{
	HexChangeData *cd;
	gint len;
	guchar *rep_data;
	gchar c_val;

	cd = (HexChangeData *)doc->undo_top->data;

	switch(cd->type) {
	case HEX_CHANGE_BYTE:
		if(cd->start >= 0 && cd->end < doc->file_size) {
			c_val = hex_document_get_byte(doc, cd->start);
			if(cd->rep_len > 0)
				hex_document_set_byte(doc, cd->v_byte, cd->start, FALSE, FALSE);
			else if(cd->rep_len == 0)
				hex_document_delete_data(doc, cd->start, 1, FALSE);
			else
				hex_document_set_byte(doc, cd->v_byte, cd->start, TRUE, FALSE);
			cd->v_byte = c_val;
		}
		break;
	case HEX_CHANGE_STRING:
		len = cd->end - cd->start + 1;
		rep_data = hex_document_get_data(doc, cd->start, len);
		hex_document_set_data(doc, cd->start, cd->rep_len, len, cd->v_string, FALSE);
		g_free(cd->v_string);
		cd->end = cd->start + cd->rep_len - 1;
		cd->rep_len = len;
		cd->v_string = rep_data;
		break;
	}

	hex_document_changed(doc, cd, FALSE);

	undo_stack_descend(doc);
}
