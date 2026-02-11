unescape_word(struct SessionHandle *data, const char *inputbuff)
{
  char *newp;
  char *dictp;
  char *ptr;
  int len;
  char byte;
  int olen=0;

  newp = curl_easy_unescape(data, inputbuff, 0, &len);
  if(!newp)
    return NULL;

  dictp = malloc(((size_t)len)*2 + 1);
  if(dictp) {


    for(ptr = newp;
        (byte = *ptr) != 0;
        ptr++) {
      if((byte <= 32) || (byte == 127) ||
          (byte == '\'') || (byte == '\"') || (byte == '\\')) {
        dictp[olen++] = '\\';
      }
      dictp[olen++] = byte;
    }
    dictp[olen]=0;

    free(newp);
  }
  return dictp;
}
