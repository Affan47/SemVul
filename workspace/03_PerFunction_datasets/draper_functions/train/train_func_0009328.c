asProperties() const
{
  if(dynamic_cast< const UnknownFrame *>(this)) {
    PropertyMap m;
    m.unsupportedData().append("UNKNOWN/" + frameID());
    return m;
  }
  const ByteVector &id = frameID();

  if(id == "TXXX")
    return dynamic_cast< const UserTextIdentificationFrame* >(this)->asProperties();
  else if(id[0] == 'T')
    return dynamic_cast< const TextIdentificationFrame* >(this)->asProperties();
  else if(id == "WXXX")
    return dynamic_cast< const UserUrlLinkFrame* >(this)->asProperties();
  else if(id[0] == 'W')
    return dynamic_cast< const UrlLinkFrame* >(this)->asProperties();
  else if(id == "COMM")
    return dynamic_cast< const CommentsFrame* >(this)->asProperties();
  else if(id == "USLT")
    return dynamic_cast< const UnsynchronizedLyricsFrame* >(this)->asProperties();
  else if(id == "UFID")
    return dynamic_cast< const UniqueFileIdentifierFrame* >(this)->asProperties();
  PropertyMap m;
  m.unsupportedData().append(id);
  return m;
}
