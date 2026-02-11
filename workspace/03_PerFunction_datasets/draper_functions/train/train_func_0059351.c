deleteMeshData()
{
  int index = 0;

  setFlagValue(GEOMETRY_TYPE, GEOMETRY_TYPE_MESH, false);
  setFlagValue(DRAW_SOURCE, DRAW_SOURCE_MESH, false);

  theControlCenter->getGui()->updateModelFlags(this);
  theControlCenter->getGui()->configureButtons("draw_source_mesh", 0);

  delete meshData; meshData = NULL;
  delete meshInfo; meshInfo = NULL;
  delete meshBox;  meshBox  = NULL;

  index = 0;
  while(true) {
    Body* body = getBody(index++);
    if (body==NULL) break;
    body->deleteMeshElements();
  }

  index = 0;
  while(true) {
    BodyElement* be = getBoundary(index++);
    if (be==NULL) break;
    be->deleteMeshElements();
  }
}
