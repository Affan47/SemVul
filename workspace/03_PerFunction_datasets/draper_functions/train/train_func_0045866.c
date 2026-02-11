mn_start_restore(int fd, const erlang_pid *self, erlang_pid *mnesia, const char *mntab, long *count, long *maxkey,long *maxobj)
{
  char buf[EISMALLBUF];
  char *bufp=buf;
  char tmpbuf[64];
  int index = 0;
  erlang_msg msg;
  int arity;
  int version;
  int i;
  int needlink;
  int needmsg;
  int msglen;


  ei_encode_version(buf,&index);
  ei_encode_tuple_header(buf,&index,2);
  ei_encode_pid(buf,&index,self);
  ei_encode_tuple_header(buf,&index,5);
  ei_encode_atom(buf,&index,"call");
  ei_encode_atom(buf,&index,EI_MNESIA_MODULE);
  ei_encode_atom(buf,&index,EI_MNESIA_RESTORE);
  ei_encode_list_header(buf,&index,2);
  ei_encode_atom(buf,&index,mntab);
  ei_encode_pid(buf,&index,self);
  ei_encode_empty_list(buf,&index);
  ei_encode_atom(buf,&index,"user");


  if (ei_send_reg_encoded(fd,self,"rex",buf,index)) return -1;


  needlink = needmsg = 1;
  while (needlink || needmsg) {

    index = EISMALLBUF;
    while (!(i = ei_recv_internal(fd,&bufp,&index,&msg,&msglen,1,0))) index = EISMALLBUF;

    switch (i) {
    case ERL_LINK:

      if (!needlink) return -1;
      needlink = 0;
      break;

    case ERL_SEND:

      if (!needmsg) return -1;
      else {

	index = 0;
	if (ei_decode_version(buf,&index,&version)
	    || ei_decode_tuple_header(buf,&index,&arity)
	    || (arity != 2)
	    || ei_decode_atom(buf,&index,tmpbuf)
	    || strcmp(tmpbuf,"rex")
	    || ei_decode_tuple_header(buf,&index,&arity)
	    || (arity != 5)
	    || ei_decode_atom(buf,&index,tmpbuf)
	    || strcmp(tmpbuf,EI_MNESIA_SIZE)
	    || ei_decode_pid(buf,&index,mnesia)
	    || ei_decode_long(buf,&index,count)
	    || ei_decode_long(buf,&index,maxkey)
	    || ei_decode_long(buf,&index,maxobj))
	  return -1;


	needmsg = 0;
      }
      break;

    default:
      return -1;
    }
  }
  return 0;
}
