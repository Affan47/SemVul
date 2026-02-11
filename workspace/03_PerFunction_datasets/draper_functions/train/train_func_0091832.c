removeAssociation(int rtti, bool reallyDelete)
{
  if (rtti==0) {
    if (reallyDelete)
      qDeleteAll(_associations);
    _associations.clear();
    return;
  }

  foreach(TraceAssociation* a, _associations) {
    if (a->rtti() == rtti) {
      if (reallyDelete) delete a;
      _associations.removeAll(a);
      return;
    }
  }
}
