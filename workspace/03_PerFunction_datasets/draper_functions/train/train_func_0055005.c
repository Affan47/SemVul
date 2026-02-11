Base64_encode(const char *data,
		  const unsigned int len,
		  char **out_data,
		  unsigned int *out_len)
{
  unsigned int  i;
  char          c;
  char         *pchar;

  *out_data = (char *)malloc(len*2.5);
  if(!*out_data){
    fprintf(stderr, "STEER: Base64_encode: malloc failed\n");
    return REG_FAILURE;
  }

  pchar = *out_data;
  for (i = 0; i < len; ++i) {

    c = (data[i] >> 2) & 0x3f;
    *(pchar++) = Base64Table[(int)c];
    c = (data[i] << 4) & 0x3f;
    if (++i < len)
      c |= (data[i] >> 4) & 0x0f;

    *(pchar++) = Base64Table[(int)c];
    if (i < len) {

      c = (data[i] << 2) & 0x3f;
      if (++i < len)
	c |= (data[i] >> 6) & 0x03;

      *(pchar++) = Base64Table[(int)c];
    }
    else{

      ++i;
      *(pchar++) = fillchar;
    }

    if (i < len) {

      c = data[i] & 0x3f;
      *(pchar++) = Base64Table[(int)c];
    }
    else{

      *(pchar++) = fillchar;
    }
  }

  *out_len = (unsigned int)(pchar - *out_data);
  return REG_SUCCESS;
}
