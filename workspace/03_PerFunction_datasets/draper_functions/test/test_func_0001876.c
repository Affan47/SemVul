data_format_line(char *outbuffer, char *inbuffer, int len)
{
  int index;
  int outbufferindex = 0;

  for(index = 0; (outbufferindex < len) && (index < 64); index++) {
    switch(inbuffer[index]) {
    case '\t':
      outbuffer[outbufferindex++] = '\\';
      outbuffer[outbufferindex++] = 't';
      break;
    case '\n':
      outbuffer[outbufferindex++] = '\\';
      outbuffer[outbufferindex++] = 'n';
      break;
    case '\0':
      outbuffer[outbufferindex] = '\0';
      return 0;
    default:
      outbuffer[outbufferindex++] = inbuffer[index];
      break;
    }
  }

  outbuffer[outbufferindex] = '\0';
  return 0;
}
