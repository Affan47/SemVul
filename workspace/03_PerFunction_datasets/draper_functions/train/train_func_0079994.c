operator()(char *buffer, size_t buflen)
{
  size_t bufpos = 0;

  while (bufpos < buflen) {
    if (buffer[bufpos] != '\0' &&
        buffer[bufpos] != '\n') ++bufpos;
    else {
      if (bufpos > 0)
        current_line.append(buffer, buffer + bufpos);

      buffer += bufpos + 1;
      buflen -= bufpos + 1;
      bufpos = 0;


      bool ret = this->operator()(current_line);
      current_line = "";

      if (!ret) return false;
    }
  }


  if (buflen > 0)
    current_line.append(buffer, buffer + buflen);

  return true;
}
