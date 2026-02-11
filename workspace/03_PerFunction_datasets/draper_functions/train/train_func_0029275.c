apply(ht_text_editor *te)
{
	if (len2) te->delete_chars(apos.line, apos.pofs, len2);
	te->goto_line(apos.line);
	te->cursor_pput(apos.pofs);
	if (string) {
		uint l = te->get_line_length(apos.line);
		cpos.line = apos.line;
		if (apos.pofs > l) {
			uint k = apos.pofs - l;
			te->indent(apos.line, l, k);
			cpos.pofs = l;
		} else {
			cpos.pofs = apos.pofs;
		}
		te->insert_chars(apos.line, apos.pofs, string, len);
	}
	te->goto_line(bpos.line);
	te->cursor_pput(bpos.pofs);
}
