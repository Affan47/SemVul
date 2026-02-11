run_mem(char *pc, value mem, value curr_pos) {
  for (;;) {
    unsigned char dst, src ;

    dst = *pc++ ;
    if (dst == 0xff)
      return ;
    src = *pc++ ;
    if (src == 0xff) {

      Field(mem,dst) = curr_pos ;
    } else {

      Field(mem,dst) = Field(mem,src) ;
    }
  }
}
