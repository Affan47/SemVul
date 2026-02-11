add_fixed_characters(string &source, string &dest, bool in_pre_text)
{
	int source_length;
	bool in_spaces = false;

	source_length = source.length();
	for (int offset = 0; offset < source_length; offset++) {
		if (source[offset] == '\n') {
			if (in_pre_text) {
				if (offset == (source_length - 1)) {
					dest += '\n';
				} else {
					dest += "\n.br\n";
				}
				in_spaces = false;
			} else {
				if (!in_spaces) {
					dest += " ";
				}
				in_spaces = true;
			}
		} else if (source[offset] == '&') {

			if (offset == (source_length - 1) || isspace(source[offset+1])) {

				dest += source[offset];
			} else {


				string entity;
				int old_offset;
				old_offset = offset;
				offset++;
				while (offset < source_length) {
					if (source[offset] == ';' || source[offset] == '\n') {
						break;
					} else {
						entity += source[offset];
						offset++;
					}
				}
				if (!entity.compare("lt")) {
					dest += '<';
				} else if (!entity.compare("gt")) {
					dest += '>';
				} else if (!entity.compare("amp")) {
					dest += '&';
				} else if (!entity.compare("nbsp")) {
					dest += ' ';
				} else if (!entity.compare("#160")) {
					dest += ' ';
				} else if (!entity.compare("#169")) {
					dest += "(C)";
				} else {

					offset = old_offset;
					dest += '&';
				}
			}
			in_spaces = false;
		} else if (source[offset] == '\\') {
			dest += "\\\\";
		} else if (!in_pre_text && source[offset] == ' ' || source[offset] == '\t') {
			if (!in_spaces) {
				dest += ' ';
			}
			in_spaces = true;
		} else {
			in_spaces = false;
			dest += source[offset];
		}
	}
	return;
}
