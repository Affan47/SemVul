applix_parse_cellref (ApplixReadState *state, unsigned char *buffer,
		      Sheet **sheet, GnmCellPos *pos,
		      char const separator)
{
	*sheet = applix_parse_sheet (state, &buffer, separator);


	if (*sheet) {
		buffer = (unsigned char *)applix_cellpos_parse
			(buffer, *sheet, pos, FALSE);
		if (buffer)
			return buffer;
	}

	*sheet = NULL;
	pos->col = pos->row = -1;
	return NULL;
}
