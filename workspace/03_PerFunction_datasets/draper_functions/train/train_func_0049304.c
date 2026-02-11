parse(GooString *encodingNameA) {
  FILE *f;
  UnicodeMap *map;
  UnicodeMapRange *range;
  UnicodeMapExt *eMap;
  int size, eMapsSize;
  char buf[256];
  int line, nBytes, i, x;
  char *tok1, *tok2, *tok3;

  if (!(f = globalParams->getUnicodeMapFile(encodingNameA))) {
    error(-1, "Couldn't find unicodeMap file for the '%s' encoding",
	  encodingNameA->getCString());
    return NULL;
  }

  map = new UnicodeMap(encodingNameA->copy());

  size = 8;
  map->ranges = (UnicodeMapRange *)gmallocn(size, sizeof(UnicodeMapRange));
  eMapsSize = 0;

  line = 1;
  while (getLine(buf, sizeof(buf), f)) {
    if ((tok1 = strtok(buf, " \t\r\n")) &&
	(tok2 = strtok(NULL, " \t\r\n"))) {
      if (!(tok3 = strtok(NULL, " \t\r\n"))) {
	tok3 = tok2;
	tok2 = tok1;
      }
      nBytes = strlen(tok3) / 2;
      if (nBytes <= 4) {
	if (map->len == size) {
	  size *= 2;
	  map->ranges = (UnicodeMapRange *)
	    greallocn(map->ranges, size, sizeof(UnicodeMapRange));
	}
	range = &map->ranges[map->len];
	sscanf(tok1, "%x", &range->start);
	sscanf(tok2, "%x", &range->end);
	sscanf(tok3, "%x", &range->code);
	range->nBytes = nBytes;
	++map->len;
      } else if (tok2 == tok1) {
	if (map->eMapsLen == eMapsSize) {
	  eMapsSize += 16;
	  map->eMaps = (UnicodeMapExt *)
	    greallocn(map->eMaps, eMapsSize, sizeof(UnicodeMapExt));
	}
	eMap = &map->eMaps[map->eMapsLen];
	sscanf(tok1, "%x", &eMap->u);
	for (i = 0; i < nBytes; ++i) {
	  sscanf(tok3 + i*2, "%2x", &x);
	  eMap->code[i] = (char)x;
	}
	eMap->nBytes = nBytes;
	++map->eMapsLen;
      } else {
	error(-1, "Bad line (%d) in unicodeMap file for the '%s' encoding",
	      line, encodingNameA->getCString());
      }
    } else {
      error(-1, "Bad line (%d) in unicodeMap file for the '%s' encoding",
	    line, encodingNameA->getCString());
    }
    ++line;
  }

  fclose(f);

  return map;
}
