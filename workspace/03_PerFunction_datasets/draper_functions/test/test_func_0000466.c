MR_computeTreeAND(Tree *l,Tree *r)
#else
Tree *MR_computeTreeAND(l,r)
    Tree    *l;
    Tree    *r;
#endif
{
    Tree    *result=NULL;
    Tree    **tail;
    Tree    *p;
    Tree    *q;
    Tree    *match;

    if (l == NULL) return tdup(r);
    if (r == NULL) return tdup(l);

    for (p=l; p != NULL; p=p->right) {

      require (p->token != ALT,"MR_computeTreeAND: p->ALT unexpected\n");
    };
    for (q=r; q != NULL; q=q->right) {

      require(q->token != ALT,"MR_computeTreeAND: q->ALT unexpected\n");
    };

    result=tnode(ALT);
    tail=&(result->down);

    for (p=l; p != NULL ; p=p->right) {
      for (q=r; q != NULL ; q=q->right) {
        if (p->token == q->token) {
          match=tnode(p->token);
          match->down=MR_computeTreeAND(p->down,q->down);
          *tail=match;
          tail=&(match->right);
        };
      };
    };

    *tail=NULL;
    result=tshrink(result);
    result=tflatten( result );
    result=tleft_factor( result );
    return result;
}
