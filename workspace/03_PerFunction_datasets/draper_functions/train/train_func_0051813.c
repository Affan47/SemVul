read(bool readProperties, Properties::ReadStyle propertiesStyle)
{


  d->ID3v2Location = findID3v2();

  if(d->ID3v2Location >= 0) {

    d->tag.set(ID3v2Index, new ID3v2::Tag(this, d->ID3v2Location, d->ID3v2FrameFactory));

    d->ID3v2OriginalSize = ID3v2Tag()->header()->completeTagSize();

    if(ID3v2Tag()->header()->tagSize() <= 0)
      d->tag.set(ID3v2Index, 0);
    else
      d->hasID3v2 = true;
  }


  d->ID3v1Location = findID3v1();

  if(d->ID3v1Location >= 0) {
    d->tag.set(ID3v1Index, new ID3v1::Tag(this, d->ID3v1Location));
    d->hasID3v1 = true;
  }


  findAPE();

  if(d->APELocation >= 0) {

    d->tag.set(APEIndex, new APE::Tag(this, d->APEFooterLocation));
    d->APEOriginalSize = APETag()->footer()->completeTagSize();
    d->hasAPE = true;
  }

  if(readProperties)
    d->properties = new Properties(this, propertiesStyle);


  ID3v2Tag(true);
  ID3v1Tag(true);
}
