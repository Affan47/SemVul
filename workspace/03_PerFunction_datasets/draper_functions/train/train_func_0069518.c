readXRefStreamSection(Stream *xrefStr, int *w, int first, int n) {
  unsigned long long offset;
  int type, gen, c, i, j;

  if (first + n < 0) {
    return gFalse;
  }
  if (first + n > size) {
    if (resize(first + n) != size) {
      error(errSyntaxError, -1, "Invalid 'size' inside xref table");
      return gFalse;
    }
    if (first + n > size) {
      error(errSyntaxError, -1, "Invalid 'first' or 'n' inside xref table");
      return gFalse;
    }
  }
  for (i = first; i < first + n; ++i) {
    if (w[0] == 0) {
      type = 1;
    } else {
      for (type = 0, j = 0; j < w[0]; ++j) {
	if ((c = xrefStr->getChar()) == EOF) {
	  return gFalse;
	}
	type = (type << 8) + c;
      }
    }
    for (offset = 0, j = 0; j < w[1]; ++j) {
      if ((c = xrefStr->getChar()) == EOF) {
	return gFalse;
      }
      offset = (offset << 8) + c;
    }
    if (offset > (unsigned long long)GoffsetMax()) {
      error(errSyntaxError, -1, "Offset inside xref table too large for fseek");
      return gFalse;
    }
    for (gen = 0, j = 0; j < w[2]; ++j) {
      if ((c = xrefStr->getChar()) == EOF) {
	return gFalse;
      }
      gen = (gen << 8) + c;
    }
    if (entries[i].offset == -1) {
      switch (type) {
      case 0:
	entries[i].offset = offset;
	entries[i].gen = gen;
	entries[i].type = xrefEntryFree;
	break;
      case 1:
	entries[i].offset = offset;
	entries[i].gen = gen;
	entries[i].type = xrefEntryUncompressed;
	break;
      case 2:
	entries[i].offset = offset;
	entries[i].gen = gen;
	entries[i].type = xrefEntryCompressed;
	break;
      default:
	return gFalse;
      }
    }
  }

  return gTrue;
}
