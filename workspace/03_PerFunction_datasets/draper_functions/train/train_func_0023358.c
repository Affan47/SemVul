put_line_32(char *psrc, char *pdst,  int dst_w, int xoffset_table[])
{
  int x;
  for (x = 0; x < dst_w; x++) {
    *pdst++=*(psrc+4*xoffset_table[x]+0);
    *pdst++=*(psrc+4*xoffset_table[x]+1);
    *pdst++=*(psrc+4*xoffset_table[x]+2);
    *pdst++=*(psrc+4*xoffset_table[x]+3);
  }
}
