getText (void)
{
  GBool oneRot = gTrue;
  GooString *s;
  TextLineFrag *frag;
  int i, col;
  GBool multiLine;
  UnicodeMap *uMap;
  char space[8], eol[16];
  int spaceLen, eolLen;

  s = new GooString();

  uMap = globalParams->getTextEncoding();

  if (uMap == NULL)
      return s;

  spaceLen = uMap->mapUnicode(0x20, space, sizeof(space));
  eolLen = uMap->mapUnicode(0x0a, eol, sizeof(eol));

  if (nFrags > 0) {
    for (i = 0; i < nFrags; ++i) {
      frags[i].computeCoords(oneRot);
    }
    page->assignColumns(frags, nFrags, oneRot);


    if (oneRot) {
      qsort(frags, nFrags, sizeof(TextLineFrag),
	    &TextLineFrag::cmpYXLineRot);
    } else {
      qsort(frags, nFrags, sizeof(TextLineFrag),
	    &TextLineFrag::cmpYXPrimaryRot);
    }

    col = 0;
    multiLine = gFalse;
    for (i = 0; i < nFrags; ++i) {
      frag = &frags[i];


      if (frag->col < col ||
	  (i > 0 && fabs(frag->base - frags[i-1].base) >
	              maxIntraLineDelta * frags[i-1].line->words->fontSize)) {
	  s->append(eol, eolLen);
	col = 0;
	multiLine = gTrue;
      }


      for (; col < frag->col; ++col) {
	s->append(space, spaceLen);
      }


      col += page->dumpFragment(frag->line->text + frag->start, frag->len, uMap, s);
    }

    if (multiLine) {
      s->append(eol, eolLen);
    }
  }

  uMap->decRefCnt();

  return s;
}
