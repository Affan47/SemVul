PLerror(const char *s)
{
  std::ostringstream ss;
  ss << CVC3::parserTemp->fileName << ":" << CVC3::parserTemp->lineNum
     << ": " << s;
  return CVC3::parserTemp->error(ss.str());
}
