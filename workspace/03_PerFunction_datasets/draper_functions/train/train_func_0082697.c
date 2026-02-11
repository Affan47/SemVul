getCurrentBoundingBox(RangeVector rv)
{
  BoundBox current_box(rv);
  RangeVector body_rv;

  int index = 0;
  while (true) {
    Body* body = getBody(index++);
    if (body==NULL) break;
    if ( !DM_HIDDEN == body->getDrawMode() ) {
      body->getRangeVector(body_rv);
      current_box.extendByRange(body_rv);
    }
  }

  current_box.getRangeVector(rv);
}
