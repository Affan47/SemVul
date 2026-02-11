setRecordCommon(const int groupcode, const dimeParam &param,
                                  const int index, dimeMemHandler * const memhandler)
{

  if (groupcode == 8 && this->isOfType(dimeBase::dimeEntityType)) {
    fprintf( stderr, "Cannot set layer name in setRecord()!\n");
    assert(0);
    return;
  }
  else if (groupcode == 2 && this->typeId() == dimeBase::dimeInsertType) {
    fprintf( stderr, "Cannot set block name for INSERT entities using setRecord()\n");
    assert(0);
    return;
  }

  if (!this->handleRecord(groupcode, param, memhandler)) {
    dimeRecord *record = this->findRecord(groupcode, index);
    if (!record) {
      record = dimeRecord::createRecord(groupcode, memhandler);
      if (!record) {
	fprintf( stderr, "Could not create record for group code: %d\n", groupcode);
	return;
      }
      dimeRecord **newarray = ARRAY_NEW(memhandler, dimeRecord*,
					this->numRecords+1);
      memcpy(newarray, this->records, this->numRecords*sizeof(dimeRecord*));
      if (!memhandler) delete [] this->records;
      this->records = newarray;
      this->records[this->numRecords++] = record;
    }
    record->setValue(param);
  }
}
