convert_lineends(struct SessionHandle *data,
                               char *startPtr, size_t size)
{
  char *inPtr, *outPtr;


  if ((startPtr == NULL) || (size < 1)) {
    return(size);
  }

  if (data->state.prev_block_had_trailing_cr == TRUE) {


    if (*startPtr == '\n') {


      memcpy(startPtr, startPtr+1, size-1);
      size--;

      data->state.crlf_conversions++;
    }
    data->state.prev_block_had_trailing_cr = FALSE;
  }


  inPtr = outPtr = memchr(startPtr, '\r', size);
  if (inPtr) {

    while (inPtr < (startPtr+size-1)) {

      if (memcmp(inPtr, "\r\n", 2) == 0) {

        inPtr++;
        *outPtr = *inPtr;

        data->state.crlf_conversions++;
      }
      else {
        if (*inPtr == '\r') {

          *outPtr = '\n';
        }
        else {

          *outPtr = *inPtr;
        }
      }
      outPtr++;
      inPtr++;
    }

    if (inPtr < startPtr+size) {

      if (*inPtr == '\r') {

        *outPtr = '\n';

        data->state.prev_block_had_trailing_cr = TRUE;
      }
      else {

        *outPtr = *inPtr;
      }
      outPtr++;
      inPtr++;
    }
    if (outPtr < startPtr+size) {

      *outPtr = '\0';
    }
    return(outPtr - startPtr);
  }
  return(size);
}
