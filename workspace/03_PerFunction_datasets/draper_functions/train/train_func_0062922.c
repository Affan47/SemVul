get(MSAttrValueList& avList_)
{
  avList_<<MSAttrValue("alignment",alignment()==MSLeft?"MSLeft":"MSCenter",
                       MSStringVector("MSLeft\nMSCenter"));
  return MSMenuItem::get(avList_);
}
