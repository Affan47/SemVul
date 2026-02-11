setupForms(Dict *resDict) {
  Object xObjDict, xObj, xObjRef, subtypeObj;
  int i;

  if (!preload) {
    return;
  }

  resDict->lookup("XObject", &xObjDict);
  if (xObjDict.isDict()) {
    for (i = 0; i < xObjDict.dictGetLength(); ++i) {
      xObjDict.dictGetValNF(i, &xObjRef);
      xObjDict.dictGetVal(i, &xObj);
      if (xObj.isStream()) {
	xObj.streamGetDict()->lookup("Subtype", &subtypeObj);
	if (subtypeObj.isName("Form")) {
	  if (xObjRef.isRef()) {
	    setupForm(xObjRef.getRef(), &xObj);
	  } else {
	    error(-1, "Form in resource dict is not an indirect reference");
	  }
	}
	subtypeObj.free();
      }
      xObj.free();
      xObjRef.free();
    }
  }
  xObjDict.free();
}
