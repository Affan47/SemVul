clear_workspace(WORKSPACE *ws)
{
  if (!ws) return;
  alberta_free(ws->work, ws->size);
  ws->work = nil;
  ws->size = 0;
  return;
}
