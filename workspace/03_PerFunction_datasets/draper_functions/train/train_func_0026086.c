tdup_chain( Tree *t )
#else
tdup_chain( t )
Tree *t;
#endif
{
	Tree *u;

	if ( t == NULL ) return NULL;
	u = tnode(t->token);
	u->v.rk = t->v.rk;
	u->down = tdup(t->down);
	return u;
}
