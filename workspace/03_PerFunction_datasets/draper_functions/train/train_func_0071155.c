match()
{

  if (partner)
    return false;

  for (int i=0; i<radix; i++) {
    if (connections[i]) {
      vertex* v = (vertex*)(connections[i]->otherSide(this));
      if (!v->partner) {

	partner = connections[i];
	v->partner = connections[i];
	return true;
      }
    }
  }
  return false;
}
