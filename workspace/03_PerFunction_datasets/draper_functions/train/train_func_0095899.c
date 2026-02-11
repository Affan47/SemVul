Lispinput(std::istream& is, char* buf, int size) {
  int res;
  if(is) {


    if(CVC3::parserTemp->interactive) {

      std::cout << CVC3::parserTemp->getPrompt() << std::flush;

      CVC3::parserTemp->setPrompt2();

      is.getline(buf, size-1);
    } else
      is.getline(buf, size-1, 0);


    bool partialStr = is.fail() && !is.eof();
    if(partialStr)
      is.clear();

    for(res = 0; res<size && buf[res] != 0; res++);
    if(res == size) Lisperror("Lexer bug: overfilled the buffer");
    if(!partialStr) {
      buf[res++] = '\n';
      buf[res] = '\0';
    }
  } else {
    res = YY_NULL;
  }
  return res;
}
