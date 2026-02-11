saveAsIpePage(Stream &stream) const
{
  BitmapFinder bmFinder;
  bmFinder.scanPage(this);
  stream << "<ipepage>\n";
  int id = 1;
  for (std::vector<Bitmap>::const_iterator it = bmFinder.iBitmaps.begin();
       it != bmFinder.iBitmaps.end(); ++it) {
    Bitmap bm = *it;
    bm.saveAsXml(stream, id);
    bm.setObjNum(id);
    ++id;
  }
  saveAsXml(stream);
  stream << "</ipepage>\n";
}
