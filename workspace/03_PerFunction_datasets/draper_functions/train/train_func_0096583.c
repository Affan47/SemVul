copy(dimeModel * const model) const
{
  dimeMemHandler *memh = model->getMemHandler();
  dimeUnknownClass *u = new(memh) dimeUnknownClass(this->dxfClassName, memh);
  if (!this->copyRecords(u, model)) {
    if (!memh) delete u;
    u = NULL;
  }
  return u;
}
