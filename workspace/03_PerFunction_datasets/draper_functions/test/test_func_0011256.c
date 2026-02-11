write(dimeOutput * const file)
{
  if (file->writeGroupCode(2) && file->writeString(sectionName)) {
    int i, n = this->tables.count();
    for (i = 0; i < n; i++) {
      if (!this->tables[i]->write(file)) break;
    }
    if (i == n) {
      return file->writeGroupCode(0) && file->writeString("ENDSEC");
    }
  }
  return false;
}
