block_dcls()
{
    register struct token *t;


    while (t = tok_class()) {
	switch (t->tokno) {
	case TOK_WSPACE:
	case '\n':
	    tok_flush(t);
	    break;
	case TOK_WORD:
	    tok_flush(t);
	    t = tok_class();

	case TOK_COMPOSITE:
	    if ((t = dcl_flush(t)) == 0)
		break;

	default:
	    DPRINTF("/* end dcls */");

	case '}':
	    tok_unget(t);
	    return;
	}
    }
}
