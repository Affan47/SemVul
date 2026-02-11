close1(nfa_node *node, int o, set *b)
#else
void close1(node,o,b)
nfa_node *node;
int o;
set *b;
#endif
{
	register nfa_node *n;


	node->nfa_set = o;
	if ((n=node->trans[0]) != NIL_INDEX && set_nil(node->label) &&
	  (n->nfa_set != o)){

		set_orel(NFA_NO(n),b);
		close1(n,o,b);
	}
	if ((n=node->trans[1]) != NIL_INDEX &&
	  (n->nfa_set != o)){

		set_orel(NFA_NO(node->trans[1]),b);
		close1(n,o,b);
	}
}
