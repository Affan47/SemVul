resetgraphemes()
{
	graphemes.clear();

	if (ustring.empty())
		return;

	const unicode_char *b=&*ustring.begin(), *e(b+ustring.size());

	do
	{
		const unicode_char *start_pos=b;

		unicode_char first, second=*b;

		do
		{
			first=second;
			++b;

		} while (b != e && (second=*b) != '\t' && first != '\t' &&
			 !unicode_grapheme_break(first, second));

		graphemes.push_back(grapheme_t(start_pos, b-start_pos));
	} while (b != e);
}
