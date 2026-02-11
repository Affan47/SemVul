nrrdKeyValueIndex(const Nrrd *nrrd, char **keyP, char **valueP,
                  unsigned int ki) {

  if (!( nrrd && keyP && valueP && ki < nrrd->kvpArr->len )) {
    if (keyP) {
      *keyP = NULL;
    }
    if (valueP) {
      *valueP = NULL;
    }
    return;
  }
  if (nrrdStateKeyValueReturnInternalPointers) {
    *keyP = nrrd->kvp[0 + 2*ki];
    *valueP = nrrd->kvp[1 + 2*ki];
  } else {
    *keyP = airStrdup(nrrd->kvp[0 + 2*ki]);
    *valueP = airStrdup(nrrd->kvp[1 + 2*ki]);
  }
  return;
}
