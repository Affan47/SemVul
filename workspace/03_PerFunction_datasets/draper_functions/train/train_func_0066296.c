func(int type,char nodetype, char *name, int value)
{
	yylval.n=malloc(sizeof(struct tree));
	yylval.n->type=type;
	yylval.n->nodetype=nodetype;
	yylval.n->name=NULL;
	if(name!=NULL)
		yylval.n->name=strdup(name);
	yylval.n->value=value;
	yylval.n->Gentry=NULL;
	yylval.n->Lentry=NULL;
	yylval.n->ptr1=NULL;
	yylval.n->ptr2=NULL;
	yylval.n->ptr3=NULL;

}
