copy(dimeModel * const model) const
{
  int i;
  dimeMemHandler *memh = model->getMemHandler();
  dimePolyline *pl = new(memh) dimePolyline;

  bool ok = pl != NULL;
  if (ok && this->indexCnt) {
    int num = this->indexCnt;
    pl->indexVertices = (dimeVertex**)
      dimeEntity::copyEntityArray((const dimeEntity**)this->indexVertices,
				 num,
				 model);
    if (num > 0 && pl->indexVertices == NULL) {
      ok = false;
    }
    else {
      pl->indexCnt = num;
      for (i = 0; i < num; i++) pl->indexVertices[i]->polyline = pl;
    }
  }
  if (ok && this->coordCnt) {
    int num = this->coordCnt;
    pl->coordVertices = (dimeVertex**)
      dimeEntity::copyEntityArray((const dimeEntity**)this->coordVertices,
				 num,
				 model);
    if (num > 0 && pl->coordVertices == NULL) {
      ok = false;
    }
    else {
      pl->coordCnt = num;
      for (i = 0; i < num; i++) pl->coordVertices[i]->polyline = pl;
    }
  }
  if (ok && this->frameCnt) {
    int num = this->frameCnt;
    pl->frameVertices = (dimeVertex**)
      dimeEntity::copyEntityArray((const dimeEntity**)this->frameVertices,
				  num,
				  model);
    if (num > 0 && pl->frameVertices == NULL) {
      ok = false;
    }
    else {
      pl->frameCnt = num;
      for (i = 0; i < num; i++) pl->frameVertices[i]->polyline = pl;
    }
  }


  if (ok) {

    for (i = 0; i < pl->coordCnt; i++)
      pl->coordVertices[i]->polyline = pl;
    for (i = 0; i < pl->indexCnt; i++)
      pl->indexVertices[i]->polyline = pl;


    pl->countM = this->countM;
    pl->countN = this->countN;
    pl->smoothCountM = this->smoothCountM;
    pl->smoothCountN = this->smoothCountN;
    pl->surfaceType = this->surfaceType;
    pl->flags = this->flags;
    pl->elevation = this->elevation;
    pl->copyExtrusionData(this);

    pl->seqend = this->seqend->copy(model);
    if (!pl->seqend) ok = false;
  }
  if (!ok || !this->copyRecords(pl, model)) {
    if (!memh) delete pl;
    pl = NULL;
  }
  return pl;
}
