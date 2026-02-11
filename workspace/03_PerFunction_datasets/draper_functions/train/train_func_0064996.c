predicate_free(Predicate *p)
#else
void predicate_free(p)
  Predicate     *p;
#endif
{
  if (p == NULL) return;
  predicate_free(p->right);
  predicate_free(p->down);
  if (p->cloned ||
      p->source == NULL ||
      p->source->guardpred == NULL ||
      p->expr == PRED_AND_LIST ||
      p->expr == PRED_OR_LIST) {
    set_free(p->scontext[1]);
    set_free(p->completionSet);
    set_free(p->completionTree);
    set_free(p->plainSet);
    Tfree(p->tcontext);
    free( (char *) p);
  } else {
    p->right=NULL;
    p->down=NULL;
  };
}
