extractGeometry(dimeArray <dimeVec3f> &verts,
			       dimeArray <int> &indices,
			       dimeVec3f &extrusionDir,
			       dxfdouble &thickness)
{
  verts.setCount(0);
  indices.setCount(0);

  verts.append(this->coords[0]);
  verts.append(this->coords[1]);
  if (this->isQuad()) {
    if (this->swapQuadCoords()) {
      verts.append(this->coords[3]);
      verts.append(this->coords[2]);
    }
    else {
      verts.append(this->coords[2]);
      verts.append(this->coords[3]);
    }
  }
  else {
    verts.append(this->coords[2]);
  }

  thickness = getThickness();
  getExtrusionDir(extrusionDir);

  return dimeEntity::POLYGONS;
}
