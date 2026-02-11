linear_insert(Mindex mdx, Term t)
{
  Plist p = get_plist();
  p->v = t;
  p->next = NULL;
  if (mdx->linear_last != NULL)
    mdx->linear_last->next = p;
  else
    mdx->linear_first = p;
  mdx->linear_last = p;
}
