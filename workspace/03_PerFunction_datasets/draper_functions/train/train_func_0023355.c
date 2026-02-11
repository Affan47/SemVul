parse_response(const std::string& str) {
  std::map<std::string,std::string> vals;
  std::list<std::string> lines;
  tokenize(str,lines,"\r\n");
  for(std::list<std::string>::iterator line = lines.begin();
                          line != lines.end();++line) {
    std::list<std::string> tokens;


    std::string::size_type pos = (*line).find_first_of("=");
    if(pos!=std::string::npos)(*line).replace(pos,1,"+");

    tokenize(*line,tokens,"+");
    if(tokens.size() != 2) continue;
    vals[*tokens.begin()] += vals[*tokens.begin()].empty()? (*(++tokens.begin())) : ("; " + *(++tokens.begin()));
  }
  return vals;
}
