parseAnnotExternalData(Dict* dict) {
  Object obj1;
  AnnotExternalDataType type;

  if (dict->lookup("Subtype", &obj1)->isName()) {
    const char *typeName = obj1.getName();

    if (!strcmp(typeName, "Markup3D")) {
      type = annotExternalDataMarkup3D;
    } else {
      type = annotExternalDataMarkupUnknown;
    }
  } else {
    type = annotExternalDataMarkupUnknown;
  }
  obj1.free();

  return type;
}
