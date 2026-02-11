read(bool readProperties, Properties::ReadStyle )
{


  d->ID3v1Location = findID3v1();

  if(d->ID3v1Location >= 0) {
    d->tag.set(ID3v1Index, new ID3v1::Tag(this, d->ID3v1Location));
    d->hasID3v1 = true;
  }


  d->APELocation = findAPE();

  if(d->APELocation >= 0) {
    d->tag.set(APEIndex, new APE::Tag(this, d->APELocation));
    d->APESize = APETag()->footer()->completeTagSize();
    d->APELocation = d->APELocation + APETag()->footer()->size() - d->APESize;
    d->hasAPE = true;
  }

  if(!d->hasID3v1)
    APETag(true);


  if(readProperties) {
    seek(0);
    d->properties = new Properties(readBlock(WavPack::HeaderSize),
                                   length() - d->APESize);
  }
}
