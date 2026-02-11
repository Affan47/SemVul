limnObjectDepthSortParts(limnObject *obj) {
  limnPart *part;
  limnVertex *vert;
  limnFace *face;
  limnEdge *edge;
  unsigned int partIdx, ii;

  for (partIdx=0; partIdx<obj->partNum; partIdx++) {
    part = obj->part[partIdx];
    part->depth = 0;
    for (ii=0; ii<part->vertIdxNum; ii++) {
      vert = obj->vert + part->vertIdx[ii];
      part->depth += vert->coord[2];
    }
    part->depth /= part->vertIdxNum;
  }

  qsort(obj->part, obj->partNum, sizeof(limnPart*), _limnPartDepthCompare);


  for (partIdx=0; partIdx<obj->partNum; partIdx++) {
    part = obj->part[partIdx];
    for (ii=0; ii<part->edgeIdxNum; ii++) {
      edge = obj->edge + part->edgeIdx[ii];
      edge->partIdx = partIdx;
    }
    for (ii=0; ii<part->faceIdxNum; ii++) {
      face = obj->face + part->faceIdx[ii];
      face->partIdx = partIdx;
    }
  }

  return 0;
}
