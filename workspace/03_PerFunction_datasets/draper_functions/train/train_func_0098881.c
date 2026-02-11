handleRecord(const int groupcode,
			const dimeParam &param,
			dimeMemHandler * const memhandler)
{
  switch(groupcode) {
  case 70:
    this->flags = param.int16_data;
    return true;
  case 10:
  case 20:
  case 30:
    this->coords[groupcode/10-1] = param.double_data;
    return true;
  case 71:
  case 72:
  case 73:
  case 74:
#ifdef DIME_FIXBIG
    this->indices[groupcode-71] = param.int32_data;
#else
    this->indices[groupcode-71] = param.int16_data;
#endif
    return true;
  }
  return dimeEntity::handleRecord(groupcode, param, memhandler);
}
