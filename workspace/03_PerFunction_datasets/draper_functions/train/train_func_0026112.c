getXMLInteger(char** location) {
  char* curLoc;
  char* tagEnd;
  char* buffer;
  uint32_t toReturn;
  size_t strLen;

  curLoc = *location;

  curLoc = strstr(curLoc, "<integer>");
  if(!curLoc)
    return 0;
  curLoc += sizeof("<integer>") - 1;

  tagEnd = strstr(curLoc, "</integer>");

  strLen = (size_t)(tagEnd - curLoc);
  buffer = (char*) malloc(strLen + 1);
  memcpy(buffer, curLoc, strLen);
  buffer[strLen] = '\0';

  curLoc = tagEnd + sizeof("</integer>") - 1;

  sscanf(buffer, "%d", (int32_t*)(&toReturn));

  free(buffer);

  *location = curLoc;

  return toReturn;
}
