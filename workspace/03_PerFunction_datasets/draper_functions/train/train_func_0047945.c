update(const char *key, Object *value) {

  delete modified;
  modified = timeToDateString(NULL);

  Object obj1;
  obj1.initString (modified->copy());
  annotObj.dictSet("M", &obj1);

  annotObj.dictSet(const_cast<char*>(key), value);

  xref->setModifiedObject(&annotObj, ref);
}
