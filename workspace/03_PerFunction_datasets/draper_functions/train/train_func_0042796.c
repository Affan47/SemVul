build_GLA_for_ALT( AST *alt, GLA **alt_tail )
#else
build_GLA_for_ALT( alt, alt_tail )
AST *alt;
GLA **alt_tail;
#endif
{
	GLA *elem_tail, *first;
	require(alt!=NULL, "build_GLA_for_alt: NULL tree pointer");

	first = build_GLA_for_tree(alt->down, &elem_tail);
	*alt_tail = elem_tail;
	return first;
}
