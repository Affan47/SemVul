treedepthup(YYSTYPE v, bool i)
{
  if(!v) return;
  treedepthup(v->n1,i);
  treedepthup(v->n2,i);
  v->depth++;
  v->path<<=1;
  v->path|=i;
  if(v->depth>30) yyerror("Nesting too deep in template or replacement\n");
}
