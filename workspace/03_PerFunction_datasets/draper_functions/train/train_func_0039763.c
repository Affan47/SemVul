processSysid(const StringC &sysid)
{
  if (outputOptions_.comment)
    options_.eventsWanted.addCommentDecls();
  if (outputOptions_.notation)
    options_.warnNotationSystemId = 1;
  if (outputOptions_.cdata)
    options_.eventsWanted.addMarkedSections();
  return ParserApp::processSysid(sysid);
}
