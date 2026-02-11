read_input(void)
{
  size_t rd;

  cvm_module_inbuflen = 0;
  for (cvm_module_inbuflen = 0;
       cvm_module_inbuflen <= BUFSIZE;
       cvm_module_inbuflen += rd) {
    if ((rd = read(0, cvm_module_inbuffer+cvm_module_inbuflen,
		   BUFSIZE-cvm_module_inbuflen)) == (unsigned)-1)
      return CVME_IO;
    if (rd == 0) break;
  }
  return 0;
}
