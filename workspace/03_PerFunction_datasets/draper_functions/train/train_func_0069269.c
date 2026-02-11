ei_rpc(ei_cnode* ec, int fd, char *mod, char *fun,
	   const char* inbuf, int inbuflen, ei_x_buff* x)
{
    int i, index;
    ei_term t;
    erlang_msg msg;
    char rex[MAXATOMLEN];

    if (ei_rpc_to(ec, fd, mod, fun, inbuf, inbuflen) < 0) {
	return -1;
    }

    while ((i = ei_rpc_from(ec, fd, ERL_NO_TIMEOUT, &msg, x)) == ERL_TICK)
	;

    if (i == ERL_ERROR)  return -1;

    index = 0;
    if (ei_decode_version(x->buff, &index, &i) < 0
	|| ei_decode_ei_term(x->buff, &index, &t) < 0)
	return -1;


    if (t.ei_type == ERL_SMALL_TUPLE_EXT && t.arity == 2)
	if (ei_decode_atom(x->buff, &index, rex) < 0)
	    return -1;

    x->index -= index;
    memmove(x->buff, &x->buff[index], x->index);
    return 0;
}
