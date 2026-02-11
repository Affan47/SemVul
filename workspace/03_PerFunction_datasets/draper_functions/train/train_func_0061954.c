moveLayer(int index, int newIndex)
{
  assert(0 <= index && index < int(iLayers.size())
	 && 0 <= newIndex && newIndex < int(iLayers.size()));

  SLayer layer = iLayers[index];
  iLayers.erase(iLayers.begin() + index);
  iLayers.insert(iLayers.begin() + newIndex, layer);


  for (ObjSeq::iterator it = iObjects.begin(); it != iObjects.end(); ++it) {
    int k = it->iLayer;
    if (k == index) {
      k = newIndex;
    } else {
      if (k > index)
	k -= 1;
      if (k >= newIndex)
	k += 1;
    }
    it->iLayer = k;
  }
}
