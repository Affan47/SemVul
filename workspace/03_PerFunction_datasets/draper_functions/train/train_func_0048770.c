removeUnsupportedProperties(const StringList &properties)
{
  if(d->hasAPE)
    d->tag.access<APE::Tag>(ApeAPEIndex, false)->removeUnsupportedProperties(properties);
  if(d->hasID3v1)
    d->tag.access<ID3v1::Tag>(ApeID3v1Index, false)->removeUnsupportedProperties(properties);
}
