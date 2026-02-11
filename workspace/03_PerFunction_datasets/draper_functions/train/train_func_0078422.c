PlainEnd(closure)
void *closure;
{
  PlainInfo pi = (PlainInfo)closure;

  ParsePlainData(pi);

  if (pi->off < pi->len)
  {
    MakeLine(pi, (char *)(pi->data + pi->off), pi->len - pi->off);
  }

  pi->height += pi->lineheight;
  GUISetDimensions(pi->wd, pi->width, pi->height);

  return;
}
