addPoint(const dimeVec3f &pt, void * const data)
{
  this->boundingBox->grow(pt);
  int ret = this->topnode->addPoint(pt, this->maxnodepoints);
  if (ret == this->userdataArray.count()) {
    this->userdataArray.append(data);
  }
  return ret;
}
