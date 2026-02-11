byteReverse(unsigned char *buf, unsigned longs) {

  do {


    byteSwap(buf[0], buf[3]);
    byteSwap(buf[1], buf[2]);
    buf += 4;
  } while(--longs);
}
