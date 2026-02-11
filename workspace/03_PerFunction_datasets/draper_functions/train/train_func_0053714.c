write(dimeOutput * const file)
{
  this->preWrite(file);

  file->writeGroupCode(2);
  file->writeString(this->name);
  file->writeGroupCode(70);
  file->writeInt16(this->flags);

  file->writeGroupCode(10);
  file->writeDouble(this->basePoint[0]);
  file->writeGroupCode(20);
  file->writeDouble(this->basePoint[1]);
  file->writeGroupCode(30);
  file->writeDouble(this->basePoint[2]);


  bool ret = dimeEntity::write(file);

  if (ret) {
    int i, n = this->entities.count();
    for (i = 0; i < n; i++) {
      if (!this->entities[i]->write(file)) break;
    }
    if (i == n) {
      if (this->endblock) {
	ret = this->endblock->write(file);
      }
      else {
	file->writeGroupCode(0);
	file->writeString("ENDBLK");
	file->writeGroupCode(8);
	ret = file->writeString(this->getLayerName());
      }
    }
    else ret = false;
  }
  return ret;
}
