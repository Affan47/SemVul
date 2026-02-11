hex_document_set_byte(HexDocument *doc, guchar val, guint offset,
					  gboolean insert, gboolean undoable)
{
	static HexChangeData change_data;

	if(offset <= doc->file_size) {
		if(!insert && offset == doc->file_size)
			return;

		doc->changed = TRUE;
		change_data.start = offset;
		change_data.end = offset;
		change_data.rep_len = (insert?0:1);
		change_data.v_string = NULL;
		change_data.type = HEX_CHANGE_BYTE;
		change_data.lower_nibble = FALSE;
		change_data.insert = insert;
		if(insert) {
			move_gap_to(doc, offset, 1);
			doc->gap_size--;
			doc->gap_pos++;
			doc->file_size++;
		}
		else if(doc->buffer + offset >= doc->gap_pos)
			offset += doc->gap_size;

		change_data.v_byte = doc->buffer[offset];
		doc->buffer[offset] = val;

	 	hex_document_changed(doc, &change_data, undoable);
	}
}
