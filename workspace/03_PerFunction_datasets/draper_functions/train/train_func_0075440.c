RenderEnd(wn)
ChimeraRender wn;
{
  if (wn->rh.end != NULL) CMethod(wn->rh.end)(wn->rc);
  return;
}
