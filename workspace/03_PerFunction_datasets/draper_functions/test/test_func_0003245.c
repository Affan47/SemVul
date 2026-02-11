initialize(PDFDoc *docA, Dict *dict, Object *obj) {
  Object obj1, obj2;

  if (dict->lookup("T", &obj1)->isString()) {
    label = obj1.getString()->copy();
  } else {
    label = NULL;
  }
  obj1.free();

  if (dict->lookup("Popup", &obj1)->isDict() && dict->lookupNF("Popup", &obj2)->isRef()) {
    popup = new AnnotPopup(docA, obj1.getDict(), &obj2);
  } else {
    popup = NULL;
  }
  obj1.free();

  if (dict->lookup("CA", &obj1)->isNum()) {
    opacity = obj1.getNum();
  } else {
    opacity = 1.0;
  }
  obj1.free();

  if (dict->lookup("CreationDate", &obj1)->isString()) {
    date = obj1.getString()->copy();
  } else {
    date = NULL;
  }
  obj1.free();

  if (dict->lookupNF("IRT", &obj1)->isRef()) {
    inReplyTo = obj1.getRef();
  } else {
    inReplyTo.num = 0;
    inReplyTo.gen = 0;
  }
  obj1.free();

  if (dict->lookup("Subj", &obj1)->isString()) {
    subject = obj1.getString()->copy();
  } else {
    subject = NULL;
  }
  obj1.free();

  if (dict->lookup("RT", &obj1)->isName()) {
    const char *replyName = obj1.getName();

    if (!strcmp(replyName, "R")) {
      replyTo = replyTypeR;
    } else if (!strcmp(replyName, "Group")) {
      replyTo = replyTypeGroup;
    } else {
      replyTo = replyTypeR;
    }
  } else {
    replyTo = replyTypeR;
  }
  obj1.free();

  if (dict->lookup("ExData", &obj1)->isDict()) {
    exData = parseAnnotExternalData(obj1.getDict());
  } else {
    exData = annotExternalDataMarkupUnknown;
  }
  obj1.free();
}
