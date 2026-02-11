parse(s)
char *s;
{
	Re_node val, tree, temp;
	Stack top, stk = NULL;

	if ((tree = parse_re(&s, NUL)) == NULL) return NULL;
	if (Push(&stk, tree) == NULL) return NULL;
	temp = mk_leaf(EOS, C_LIT, NUL, NULL);
	if (temp == NULL || Push(&stk, temp) == NULL) return NULL;
	final_pos = --pos_cnt;
	top = cat2(&stk);
	val = Top(top);
	free(top);
	return val;
}
