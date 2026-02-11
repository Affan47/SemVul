find_annot_movie_for_action (PopplerDocument *document,
			     LinkMovie       *link)
{
  AnnotMovie *annot = NULL;
  XRef *xref = document->doc->getXRef ();
  Object annotObj;

  if (link->hasAnnotRef ()) {
    Ref *ref = link->getAnnotRef ();

    xref->fetch (ref->num, ref->gen, &annotObj);
  } else if (link->hasAnnotTitle ()) {
    Object annots;
    GooString *title = link->getAnnotTitle ();
    int i;

    for (i = 1; i <= document->doc->getNumPages (); ++i) {
      Page *p = document->doc->getPage (i);
      if (!p) continue;

      if (p->getAnnots (&annots)->isArray ()) {
        int j;
	GBool found = gFalse;

	for (j = 0; j < annots.arrayGetLength () && !found; ++j) {
          if (annots.arrayGet(j, &annotObj)->isDict()) {
	    Object obj1;

	    if (!annotObj.dictLookup ("Subtype", &obj1)->isName ("Movie")) {
	      obj1.free ();
	      continue;
	    }
	    obj1.free ();

	    if (annotObj.dictLookup ("T", &obj1)->isString()) {
	      GooString *t = obj1.getString ();

	      if (title->cmp(t) == 0)
	        found = gTrue;
	    }
	    obj1.free ();
	  }
	  if (!found)
	    annotObj.free ();
	}
	if (found) {
	  annots.free ();
	  break;
	} else {
          annotObj.free ();
	}
      }
      annots.free ();
    }
  }

  if (annotObj.isDict ()) {
    Object tmp;

    annot = new AnnotMovie (document->doc, annotObj.getDict(), &tmp);
    if (!annot->isOk ()) {
      delete annot;
      annot = NULL;
    }
  }
  annotObj.free ();

  return annot;
}
