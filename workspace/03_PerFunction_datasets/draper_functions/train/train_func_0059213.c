removeOneInlineKeyword(
       const std::string &LeadingInlineStr,
       const std::string &InlineStr,
       const std::string &Str,
       const SourceLocation &StartLoc)
{
  if (!Str.compare(0, LeadingInlineStr.length(), LeadingInlineStr)) {
    TheRewriter.RemoveText(SourceRange(
                  StartLoc,
                  StartLoc.getLocWithOffset(LeadingInlineStr.length() - 1)));
    return true;
  }

  size_t Off = Str.find(InlineStr);
  if (Off == std::string::npos)
    return false;

  TheRewriter.RemoveText(SourceRange(
                StartLoc.getLocWithOffset(Off),
                StartLoc.getLocWithOffset(Off + InlineStr.length() - 1)));
  return true;
}
