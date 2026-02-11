getOutline()
{
  if (!outline) {

    outline = new Outline(catalog->getOutline(), xref);
  }

  return outline;
}
