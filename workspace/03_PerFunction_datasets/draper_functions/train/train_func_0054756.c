getRecord(const int groupcode,
		     dimeParam &param,
		     const int index) const
{
  switch (groupcode) {
  case 66:
    param.int16_data = this->attributesFollow;
    return true;
  case 2:
    param.string_data = this->blockName;
    return true;
  case 10:
  case 20:
  case 30:
    param.double_data = this->insertionPoint[groupcode/10-1];
    return true;
  case 210:
  case 220:
  case 230:
    param.double_data = this->extrusionDir[(groupcode-210)/10];
    return true;
  case 41:
  case 42:
  case 43:
    param.double_data = this->scale[groupcode-41];
    return true;
  case 44:
    param.double_data = this->columnSpacing;
    return true;
  case 45:
    param.double_data = this->rowSpacing;
    return true;
  case 50:
    param.double_data = this->rotAngle;
    return true;
  case 70:
    param.int16_data = this->columnCount;
    return true;
  case 71:
#ifdef DIME_FIXBIG
    param.int32_data = this->rowCount;
#else
    param.int16_data = this->rowCount;
#endif
    return true;
  }
  return dimeEntity::getRecord(groupcode, param, index);
}
