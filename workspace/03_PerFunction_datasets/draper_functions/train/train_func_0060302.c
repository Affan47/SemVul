get_scomp(comp_coder_t code)
{
 if (code==COMP_CODE_RLE)
  return "RLE";
 else if (code==COMP_CODE_SKPHUFF)
  return "HUFF";
 else if (code==COMP_CODE_DEFLATE)
  return "GZIP";
 else if (code==COMP_CODE_JPEG)
  return "JPEG";
 if (code==COMP_CODE_SZIP)
  return "SZIP";
 else if (code==COMP_CODE_NONE)
  return "NONE";
 else {
  printf("Input Error in compression type\n");
  exit(1);
 }

 return NULL;
}
