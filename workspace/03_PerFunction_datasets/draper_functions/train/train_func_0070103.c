print_unicode(char* dst, const unsigned int dst_max_length, short* src, unsigned int src_len)
{


  if (src[(src_len/2) - 1] != 0) {

    if (src[(src_len/2)] != 0) {

      src[(src_len/2)] = 0;
    } else {

      src_len += 2;
    }
  }


  if (src_len > dst_max_length) {
    src_len = dst_max_length;
    src[(src_len/2) - 1] = 0;
  }


  memcpy(dst, src, src_len);

  return src_len;
}
