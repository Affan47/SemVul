ID3v2Tag(bool create)
{
  if(!create || d->tag[ID3v2Index])
    return static_cast<ID3v2::Tag *>(d->tag[ID3v2Index]);

  d->tag.set(ID3v2Index, new ID3v2::Tag);
  return static_cast<ID3v2::Tag *>(d->tag[ID3v2Index]);
}
