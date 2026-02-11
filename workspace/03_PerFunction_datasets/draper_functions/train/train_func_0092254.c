copy(dimeModel * const model) const
{
  dimeVertex *v = new(model->getMemHandler()) dimeVertex;

  v->flags = this->flags;
  v->indices[0] = this->indices[0];
  v->indices[1] = this->indices[1];
  v->indices[2] = this->indices[2];
  v->indices[3] = this->indices[3];
  v->coords = this->coords;
  v->polyline = this->polyline;

  if (!this->copyRecords(v, model)) {

    if (!model->getMemHandler()) delete v;
    v = NULL;
  }
  return v;
}
