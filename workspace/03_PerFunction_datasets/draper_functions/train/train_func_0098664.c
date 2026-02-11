checkEncoding(const StringList &fields, String::Type encoding)
{
  if(encoding != String::Latin1)
    return encoding;

  for(StringList::ConstIterator it = fields.begin(); it != fields.end(); ++it) {
    if(!(*it).isLatin1()) {
      debug("Frame::checkEncoding() -- Rendering using UTF8.");
      return String::UTF8;
    }
  }

  return String::Latin1;
}
