make_msg
(MsgHeader* msg, int type, int encrypted, const void* rawdata, size_t siz)
{
  if(siz > raw_data_len)
    abort();

  size_t msgsiz;

  msg->type = type;
  msg->encrypted = (encrypted?1:0);

  if(!encrypted){
    msgsiz = siz;
    memcpy(msg+1, rawdata, siz);
  }else{
    msgsiz = base64_bufsize(siz);
    base64_encode((char*)(msg+1), msgsiz, rawdata, siz);
  }

  return msgsiz;
}
