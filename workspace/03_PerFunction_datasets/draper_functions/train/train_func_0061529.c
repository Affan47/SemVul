handleRecord(const int groupcode,
		     const dimeParam &param,
		     dimeMemHandler * const memhandler)
{
  switch(groupcode) {
  case 10:
  case 20:
  case 30:
    this->center[groupcode / 10 - 1] = param.double_data;
    return true;
  case 40:
    this->radius = param.double_data;
    return true;
  case 50:
    this->startAngle = param.double_data;
    return true;
  case 51:
    this->endAngle = param.double_data;
    return true;
  }
  return dimeExtrusionEntity::handleRecord(groupcode, param, memhandler);
}
