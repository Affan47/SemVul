produce(char *tbuffer,int limit,int handle) {
  int i;
  char c;
  list<char>::iterator di;

  for(di=buffer.begin();di!=buffer.end();di++)
    if (*di=='\n')
      break;

  if (di!=buffer.end()) {
    memset(tbuffer,0,limit);
    i=0;
    while(di!=buffer.begin()) {
      c=buffer.front();
      buffer.pop_front();
      if (c>=0x20)
	tbuffer[i++]=c;
    }
    buffer.pop_front();
    global.LogAppend(tbuffer);
    return 0;
  }
  return -1;
}
