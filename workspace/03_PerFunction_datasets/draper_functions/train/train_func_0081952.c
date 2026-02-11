getRecord(const int groupcode,
		     dimeParam &param,
		     const int index) const
{
  switch(groupcode) {
  case 10:
  case 20:
  case 30:
    param.double_data = this->center[groupcode/10-1];
    return true;
  case 40:
    param.double_data = this->radius;
    return true;
  }
  return dimeExtrusionEntity::getRecord(groupcode, param, index);
}
