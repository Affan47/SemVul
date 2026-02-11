handleRecord(const int groupcode,
			    const dimeParam &param,
			    dimeMemHandler * const memhandler)
{
  switch(groupcode) {
  case 2:
    this->setLayerName(param.string_data, memhandler);
    return true;
  case 62:
    this->setColorNumber(param.int16_data);
    return true;
  }
  return dimeTableEntry::handleRecord(groupcode, param, memhandler);
}
