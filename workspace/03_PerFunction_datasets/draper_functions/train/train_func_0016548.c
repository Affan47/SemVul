RenderTable(li, box, r)
HTMLInfo li;
HTMLBox box;
Region r;
{
  HTable *ts = (HTable *)box->closure;
  HTMLBox c;

  for (c = (HTMLBox)GListGetHead(ts->klist); c != NULL;
       c = (HTMLBox)GListGetNext(ts->klist))
  {
    HTMLRenderBox(li, r, c);
  }

  return;
}
