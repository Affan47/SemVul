removeView(int i)
{
  iViews.erase(iViews.begin() + i);
  for (int l = 0; l < countLayers(); ++l)
    iLayers[l].iVisible.erase(iLayers[l].iVisible.begin() + i);
}
