copy(dimeModel * const model) const
{
  dimePoint *p = new(model->getMemHandler()) dimePoint;

  p->coords = this->coords;
  p->copyExtrusionData(this);

  if (!this->copyRecords(p, model)) {

    if (!model->getMemHandler()) delete p;
    p = NULL;
  }
  return p;
}
