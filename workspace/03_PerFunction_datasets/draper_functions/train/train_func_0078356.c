make(unsigned char *data, uint32_t len, void (*destruct)(unsigned char *, size_t))
{
  WritablePacket *p = new WritablePacket;
  if (p) {
    p->_head = p->_data = data;
    p->_tail = p->_end = data + len;
    p->_destructor = destruct;
  }
  return p;
}
