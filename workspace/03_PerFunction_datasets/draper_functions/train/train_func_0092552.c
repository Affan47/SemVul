operator=(const message_buff& buff) {
  if (this != &buff) {
    if (buff.is_static) {
      msg = buff.msg;
      len = buff.len;
      is_static = true;
    } else {
      if (buff.msg)
        msg = (unsigned char *)memdup(buff.msg, buff.len);
      else
        msg = NULL;
      len = buff.len;
      is_static = false;
    }
  }
  return *this;
}
