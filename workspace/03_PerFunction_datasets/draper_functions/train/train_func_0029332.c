DestroyIFrame(li, box)
HTMLInfo li;
HTMLBox box;
{
  HTMLFrameInfo fi = (HTMLFrameInfo)box->closure;

  if (fi->cs != NULL) StackDestroy(fi->cs);

  return;
}
