Swig_feature_set(Hash *features, const_String_or_char_ptr name, SwigType *decl, const_String_or_char_ptr featurename, String *value, Hash *featureattribs) {
  Hash *n;
  Hash *fhash;

#ifdef SWIG_DEBUG
  Printf(stdout, "Swig_feature_set: '%s' '%s' '%s' '%s'\n", name, decl, featurename, value);
#endif

  n = Getattr(features, name);
  if (!n) {
    n = NewHash();
    Setattr(features, name, n);
    Delete(n);
  }
  if (!decl) {
    fhash = Getattr(n, "start");
    if (!fhash) {
      fhash = NewHash();
      Setattr(n, "start", fhash);
      Delete(fhash);
    }
  } else {
    fhash = Getattr(n, decl);
    if (!fhash) {
      String *cdecl_ = Copy(decl);
      fhash = NewHash();
      Setattr(n, cdecl_, fhash);
      Delete(cdecl_);
      Delete(fhash);
    }
  }
  if (value) {
    Setattr(fhash, featurename, value);
  } else {
    Delattr(fhash, featurename);
  }

  {

    Hash *attribs = featureattribs;
    while (attribs) {
      String *attribname = Getattr(attribs, "name");
      String *featureattribname = NewStringf("%s:%s", featurename, attribname);
      if (value) {
	String *attribvalue = Getattr(attribs, "value");
	Setattr(fhash, featureattribname, attribvalue);
      } else {
	Delattr(fhash, featureattribname);
      }
      attribs = nextSibling(attribs);
      Delete(featureattribname);
    }
  }

  if (name && SwigType_istemplate(name)) {
    String *dname = Swig_symbol_template_deftype(name, 0);
    if (Strcmp(dname, name)) {
      Swig_feature_set(features, dname, decl, featurename, value, featureattribs);
    }
    Delete(dname);
  }
}
