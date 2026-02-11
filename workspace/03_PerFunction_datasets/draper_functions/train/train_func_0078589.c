prunknowncreatedata(node *np, FILE* fp)
{
  unsigned long ve;
  switch(np->opcode)
  {
  case INTERSECTION:
    prunknowncreatedata(np->lval, fp);
    prunknowncreatedata(np->rval, fp);
    return;
  case US_ID: return;
  case US_SCALAR:
    ve=varextern(np->rval->constant,np->rval->opcode);
    fprintf(fp,"\t\t{%d,0,%lu,",np->rval->width,ve);
    break;
  case US_ARRVAR:
    ve=varextern(np->rval->constant,np->rval->opcode);
    fprintf(fp,"\t\t{%d,1,%lu,{ick_ieg277,ick_ies277},0},\n",
	    np->rval->width,ve);
    return;
  case US_ELEM:
  case US_EXPR:
    fprintf(fp,"\t\t{%d,0,0,",np->rval->width);
    break;
  default: ick_lose(IE778, emitlineno, (const char*) NULL);
  }
  if(createsused)
    fprintf(fp,"{ick_og%lx,ick_os%lx},",
	    (unsigned long)np->rval,(unsigned long)np->rval);
  else
    fprintf(fp,"{0,0},");
  prexpr(np->rval,fp,0);
  fprintf(fp,"},\n");
}
