findByOwner(const ID3v2::Tag *tag, const String &o)
{
  ID3v2::FrameList comments = tag->frameList("UFID");

  for(ID3v2::FrameList::ConstIterator it = comments.begin();
      it != comments.end();
      ++it)
  {
    UniqueFileIdentifierFrame *frame = dynamic_cast<UniqueFileIdentifierFrame *>(*it);
    if(frame && frame->owner() == o)
      return frame;
  }

  return 0;
}
