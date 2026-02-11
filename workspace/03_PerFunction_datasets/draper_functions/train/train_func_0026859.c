THX_parse_keyword_swaptwostmts(pTHX)
{
    OP *a, *b;
    a = parse_fullstmt(0);
    b = parse_fullstmt(0);
    if(a && b)
	PL_hints |= HINT_BLOCK_SCOPE;
    return op_append_list(OP_LINESEQ, b, a);
}
