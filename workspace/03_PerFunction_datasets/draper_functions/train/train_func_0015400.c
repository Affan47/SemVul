curl_easy_pause(CURL *curl, int action)
{
  struct SessionHandle *data = (struct SessionHandle *)curl;
  struct SingleRequest *k = &data->req;
  CURLcode result = CURLE_OK;


  int newstate = k->keepon &~ (KEEP_RECV_PAUSE| KEEP_SEND_PAUSE);


  newstate |= ((action & CURLPAUSE_RECV)?KEEP_RECV_PAUSE:0) |
    ((action & CURLPAUSE_SEND)?KEEP_SEND_PAUSE:0);


  k->keepon = newstate;

  if(!(newstate & KEEP_RECV_PAUSE) && data->state.tempwrite) {


    char *tempwrite = data->state.tempwrite;
    char *freewrite = tempwrite;
    size_t tempsize = data->state.tempwritesize;
    int temptype = data->state.tempwritetype;
    size_t chunklen;


    data->state.tempwrite = NULL;


    do {
      chunklen = (tempsize > CURL_MAX_WRITE_SIZE)?CURL_MAX_WRITE_SIZE:tempsize;

      result = Curl_client_write(data->easy_conn,
                                 temptype, tempwrite, chunklen);
      if(result)

        break;

      if(data->state.tempwrite && (tempsize - chunklen)) {


        char *newptr;


        newptr = realloc(data->state.tempwrite, tempsize);

        if(!newptr) {
          free(data->state.tempwrite);
          data->state.tempwrite = NULL;
          result = CURLE_OUT_OF_MEMORY;

          break;
        }
        data->state.tempwrite = newptr;
        memcpy(newptr, tempwrite, tempsize);
        data->state.tempwritesize = tempsize;

        break;
      }
      else {
        tempsize -= chunklen;
        tempwrite += chunklen;
      }

    } while((result == CURLE_OK) && tempsize);

    free(freewrite);
  }


  if(!result &&
     ((newstate&(KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) !=
      (KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) )
    Curl_expire(data, 1);

  return result;
}
