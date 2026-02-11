strip(int tags)
{
  if(tags & ID3v1) {
    d->tag.set(ID3v1Index, 0);
    APETag(true);
  }

  if(tags & ID3v2) {
    delete d->ID3v2Header;
    d->ID3v2Header = 0;
  }

  if(tags & APE) {
    d->tag.set(APEIndex, 0);

    if(!ID3v1Tag())
      APETag(true);
  }
}
