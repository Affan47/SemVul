properties() const
{


  if(d->hasID3v2)
    return d->tag.access<ID3v2::Tag>(ID3v2Index, false)->properties();
  if(d->hasAPE)
    return d->tag.access<APE::Tag>(APEIndex, false)->properties();
  if(d->hasID3v1)
    return d->tag.access<ID3v1::Tag>(ID3v1Index, false)->properties();
  return PropertyMap();
}
