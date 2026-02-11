scanner_get_word()
{
	while( (scanner_char_code(scanner_ch)==LETTER) || (scanner_char_code(scanner_ch)==DIGIT) ) {
		*scanner_tokenp++ = scanner_ch;
		scanner_get_char();
	}
	*scanner_tokenp = '\0';

	scanner_token = IDENTIFIER;
}
