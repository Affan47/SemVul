read_binary_string(std::istream& in, std::string& str)
{
  read_binary_guard(in, 0x3001);

  unsigned char len;
  read_binary_number_nocheck(in, len);
  if (len == 0xff) {
    unsigned short slen;
    read_binary_number_nocheck(in, slen);
    char * buf = new char[slen + 1];
    in.read(buf, slen);
    buf[slen] = '\0';
    str = buf;
    delete[] buf;
  }
  else if (len) {
    char buf[256];
    in.read(buf, len);
    buf[len] = '\0';
    str = buf;
  } else {
    str = "";
  }

  read_binary_guard(in, 0x3002);
}
