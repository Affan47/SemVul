prunknownstr(node *np, FILE* fp)
{
  int i;
  switch(np->opcode)
  {
  case INTERSECTION:
    i=prunknownstr(np->lval, fp);
    i+=prunknownstr(np->rval, fp);
    return i;
  case BADCHAR:
    if (np->constant > 256)
      (void) fprintf(fp, "o%xx%x",
		     (unsigned int)(np->constant / 256),
		     (unsigned int)(np->constant % 256));
    else
      (void) fprintf(fp, "u%x", (unsigned int)np->constant);
    return 2;
  case US_ID: (void) fputc((char)np->constant, fp); return 0;
  case US_ELEM: (void) fputc(';', fp); return 1;
  case US_SCALAR: (void) fputc('.', fp); return 1;
  case US_ARRVAR: (void) fputc(',', fp); return 1;
  case US_EXPR: (void) fputc('~', fp); return 1;
  default: ick_lose(IE778, emitlineno, (const char*) NULL);
  }
   return 0;
}
