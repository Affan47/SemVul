deflated() const
{
  const PdfObj *f = get("Filter", 0);
  return !(!f || !f->name() || f->name()->value() != "FlateDecode");
}
