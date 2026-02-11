Level03(void)
{
    NODE *Root;

    Root = Level04();

    if (Token == T_OPERATOR && Operator == O_CND) {
	Root = NewNode(Root);
	Parse();
	LinkNode(Root, Level04());
	if (Token == T_OPERATOR && Operator == O_COL) {
	    Parse();
	    LinkNode(Root, Level04());
	} else {
	    error("Evaluator: syntax error in <%s>: expecting ':' got '%s'", Expression, Word);
	    LinkNode(Root, JunkNode());
	}
    }

    return Root;
}
