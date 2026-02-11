gen_ly(int eob)
{
	generate();
	if (info['W' - 'A'] != 0) {
		put_words(info['W' - 'A']);
		info['W' - 'A'] = 0;
	}
	if (eob)
		buffer_eob();
}
