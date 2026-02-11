reach(unsigned *nfa_list, register int a, unsigned *reach_list)
#else
reach(nfa_list, a, reach_list)
unsigned *nfa_list;
register int a;
unsigned *reach_list;
#endif
{
	register unsigned *e;
	register nfa_node *node;
	int t=0;

	e = nfa_list;
	if (e){
		while (*e != nil){
			node = NFA(*e);
			if (set_el(a,node->label)){
				t=1;
				*reach_list=NFA_NO(node->trans[0]);
				++reach_list;
			}
			++e;
		}
	}
	*reach_list=nil;
	return t;
}
