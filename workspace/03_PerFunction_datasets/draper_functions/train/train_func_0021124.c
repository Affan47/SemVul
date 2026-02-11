erl_global_unregister(int fd, const char *name)
{
  char buf[EISMALLBUF];
  char *bufp=buf;
  char tmpbuf[64];
  int index = 0;
  erlang_pid *self = erl_self();
  erlang_msg msg;
  int i;
  int version,arity,msglen;
  int needunlink, needatom, needdemonitor;


  self->num = fd;
  ei_encode_version(buf,&index);
  ei_encode_tuple_header(buf,&index,2);
  ei_encode_pid(buf,&index,self);
  ei_encode_tuple_header(buf,&index,5);
  ei_encode_atom(buf,&index,"call");
  ei_encode_atom(buf,&index,"global");
  ei_encode_atom(buf,&index,"unregister_name_external");
  ei_encode_list_header(buf,&index,1);
  ei_encode_atom(buf,&index,name);
  ei_encode_empty_list(buf,&index);
  ei_encode_atom(buf,&index,"user");


  if (ei_send_reg_encoded(fd,self,"rex",buf,index)) return -1;


  needunlink = needatom = needdemonitor = 1;
  while (1) {

    while (1) {
      index = EISMALLBUF;
      if (!(i = ei_recv_internal(fd,&bufp,&index,&msg,&msglen,1,0))) continue;
      else break;
    }

    switch (i) {
    case ERL_UNLINK:

      if (!needunlink) return -1;
      needunlink = 0;
      break;

    case ERL_DEMONITOR_P-10:

      if (!needdemonitor) return -1;
      needdemonitor = 0;
      break;

    case ERL_SEND:

      if (!needatom) return -1;
      else {

	index = 0;
	if (ei_decode_version(buf,&index,&version)
	    || ei_decode_tuple_header(buf,&index,&arity)
	    || (arity != 2)
	    || ei_decode_atom(buf,&index,tmpbuf)
	    || strcmp(tmpbuf,"rex")
	    || ei_decode_atom(buf,&index,tmpbuf)
	    || strcmp(tmpbuf,"ok"))
	  return -1;


	return 0;
      }
      break;

    default:
      return -1;
    }
  }

  return 0;
}
