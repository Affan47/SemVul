extractGeometry(dimeArray <dimeVec3f> &verts,
			dimeArray <int> &indices,
			dimeVec3f &extrusionDir,
			dxfdouble &thickness)
{

  verts.setCount(0);
  indices.setCount(0);

  thickness = this->thickness;
  extrusionDir = this->extrusionDir;


  double end = this->endAngle;
  if (end < this->startAngle) end += 360.0;

  double delta = DXFDEG2RAD(end - this->startAngle);
  if (delta == 0.0) {
#ifndef NDEBUG
    fprintf(stderr,"ARC with startAngle == endAngle!\n");
#endif
    end += 2*M_PI;

  }


  int parts = (int) DXFABS((2*M_PI)/delta);


  int numpts = ARC_NUMPTS / parts + 1;
  if (numpts > ARC_NUMPTS) numpts = ARC_NUMPTS;

  double inc = delta / numpts;
  double rad = DXFDEG2RAD(this->startAngle);
  int i;
  for (i = 0; i < numpts; i++) {
    verts.append(dimeVec3f(this->center.x + this->radius * cos(rad),
			   this->center.y + this->radius * sin(rad),
			   this->center.z));
    rad += inc;
  }
  rad = DXFDEG2RAD(end);

  verts.append(dimeVec3f(this->center.x + this->radius * cos(rad),
			 this->center.y + this->radius * sin(rad),
			 this->center.z));

  return dimeEntity::LINES;
}
