NextAtom(OBAtomIterator &i)
  {
    ++i;
    return((i == _vatom.end()) ? (OBAtom*)NULL : (OBAtom*)*i);
  }
