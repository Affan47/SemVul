sock_receive(struct sock_state_t *s,char* buffer,int maxlen)
{
if ( ! s->error_occurred)
	{
	int tmp = recvstring( s->socket, buffer, maxlen , s->prb);

	if ( tmp < 0 )
		sock_error("recvstring",tmp,s);
	else
		sock_received(buffer,s);

	return tmp;
	}
SKIP(s,"sock_receive");
}
