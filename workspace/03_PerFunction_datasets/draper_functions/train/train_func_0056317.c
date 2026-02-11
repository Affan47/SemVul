getFullyQualifiedName() {
  Object obj1, obj2;
  Object parent;
  GooString *parent_name;
  GooString *full_name;

  if (fullyQualifiedName)
    return fullyQualifiedName;

  full_name = new GooString();

  obj.copy(&obj1);
  while (obj1.dictLookup("Parent", &parent)->isDict()) {
    if (parent.dictLookup("T", &obj2)->isString()) {
      parent_name = obj2.getString();

      if (parent_name->hasUnicodeMarker()) {
        parent_name->del(0, 2);
	full_name->insert(0, "\0.", 2);
      } else {
        full_name->insert(0, '.');
      }

      full_name->insert(0, parent_name);
      obj2.free();
    }
    obj1.free();
    parent.copy(&obj1);
    parent.free();
  }
  obj1.free();
  parent.free();

  if (partialName) {
    full_name->append(partialName);
  } else {
    int len = full_name->getLength();

    if (len > 0)
      full_name->del(len - 1, 1);
  }

  fullyQualifiedName = full_name;
  return fullyQualifiedName;
}
