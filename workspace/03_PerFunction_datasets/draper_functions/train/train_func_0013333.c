HTMLMotion(closure, x, y)
void *closure;
int x, y;
{
  HTMLInfo li = (HTMLInfo)closure;
  HTMLAnchor a;
  GList list;

  list = li->alist;
  for (a = (HTMLAnchor)GListGetHead(list); a != NULL;
       a = (HTMLAnchor)GListGetNext(list))
  {
    if (InAnchor(x, y, a->box)) break;
  }

  if (a == NULL || a->p == NULL) RenderSendMessage(li->wn, NULL);
  else HTMLPrintAnchor(li, a, x, y, false);
  li->over = a;

  return(true);
}
