copyRecords(dimeRecordHolder * const rh,
                             dimeMemHandler * const memh) const
{
  bool ok = true;
  if (this->numRecords) {
    rh->records = ARRAY_NEW(memh, dimeRecord*, this->numRecords);
    if (rh->records) {
      rh->numRecords = this->numRecords;
      for (int i = 0; i < this->numRecords; i++)
	rh->records[i] = this->records[i]->copy(memh);
    }
    else ok = false;
  }
  else {
    rh->records = NULL;
    rh->numRecords = 0;
  }
  return ok;
}
