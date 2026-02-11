getRecord(const int groupcode,
			   dimeParam &param,
			   const int index) const
{
  int i, n = this->numRecords;
  int cnt = 0;
  for (i = 0; i < n; i++) {
    if (this->records[i]->getGroupCode() == groupcode) {
      if (cnt++ == index) {
	this->records[i]->getValue(param);
	return true;
      }
    }
  }
  return false;
}
