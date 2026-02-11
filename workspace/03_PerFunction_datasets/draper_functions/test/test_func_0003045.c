toplevelURL()
{
  KHTMLPart* part = this;
  while (part->parentPart())
    part = part->parentPart();

  if (!part)
    return KUrl();

  return part->url();
}
