setCommentDelimiters(const std::list<std::string> &delimiters)
{
  myCommentDelimiterList.clear();

  int i = 0;
  for (std::list<std::string>::const_iterator iter = delimiters.begin();
       iter != delimiters.end();
       iter++, i++) {
    std::string curDelimiter = *iter;
    if (!ArUtil::isStrEmpty(curDelimiter.c_str())) {
      myCommentDelimiterList.push_back(curDelimiter);
    }
    else {
      ArLog::log(ArLog::Normal,
                 "ArFileParser::setCommentDelimiters cannot set empty delimiter at position %i",
                 i);
    }
  }

}
