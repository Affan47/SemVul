update_checkRepeat(uint8 *&dataptr, Channel &channel, uint8 value) {
  ++dataptr;
  if (--channel.repeatCounter) {
    int16 add = READ_LE_UINT16(dataptr - 2);
    dataptr += add;
  }
  return 0;
}
