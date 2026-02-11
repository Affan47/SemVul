header(const MSSymbol& tag_)
{
  MSBoolean found=MSFalse;
  for (unsigned i=0;i<headerList().count();i++) if (tag_==header(i)->printTag()) found=MSTrue;
  if (found==MSTrue) return headerParagraph(tag_);
  MSMessageLog::warningMessage("Warning: header \"%s\" not found\n",tag_.symbolName());
  return defaultParagraph();
}
