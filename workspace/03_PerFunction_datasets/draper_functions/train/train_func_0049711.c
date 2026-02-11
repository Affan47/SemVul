eval_tree(struct node_t *p)
{
    int lval,rval;
    if(!p) return 0;

    switch (p->op) {

    case O_NUM:
	return *(int *)p->left;

    case O_ID:
	return 0;

    case O_AND:
    case O_OR:
    case O_LESS:
    case O_LESSEQ:
    case O_EQ:
    case O_MOREEQ:
    case O_MORE:
	lval = eval_tree(p->left);
	rval = eval_tree(p->right);
	if(p->op == O_AND)    return (lval && rval);
	if(p->op == O_OR)     return (lval || rval);
	if(p->op == O_LESS)   return (lval < rval);
	if(p->op == O_LESSEQ) return (lval <= rval);
	if(p->op == O_EQ)     return (lval == rval);
	if(p->op == O_MORE)   return (lval >= rval);
	if(p->op == O_MOREEQ) return (lval > rval);

    default:
	return 0;
    }
}
