parse_file()
{
    int lex = scan();

    while (lex != EOF) {
	if (lex == '{') {
	    int pass_through = 1;
	    parse_block(&pass_through, ctx_typedef);
	} else if (lex == '=') {
	    lex = parse_expression();
	    continue;
	}
	lex = scan();
    }
}
