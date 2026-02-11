find(string id)
{
  scope *sc=current;

  while (sc!=0) {
    if (sc->m.find(id)!=sc->m.end()) {
      return true;
    }
    sc=sc->previous;
  }

  return false;
}
