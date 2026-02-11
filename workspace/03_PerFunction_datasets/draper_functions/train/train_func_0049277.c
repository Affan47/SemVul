getPredecessor() const
{
  vertex* v = NULL;

  for (int i=0; i<radix; i++) {
    if (pred[i]) {
      vertex* v2 = (vertex*)(pred[i]->otherSide(this));
      if (v2->inLayers) {
	v = v2;
	break;
      }
    }
  }
  return v;
}
