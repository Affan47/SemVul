CSocket_CallBack(int t_sock,int type, CSOCKET *_object)
{
	char buf[1];
	struct pollfd mypoll;
	int numpoll;
	struct timespec mywait;


	mywait.tv_sec=0;
	mywait.tv_nsec=100000;
	nanosleep(&mywait,NULL);


	if (SOCKET->status != NET_CONNECTED) return;

	mypoll.fd=t_sock;
	mypoll.events=POLLIN | POLLNVAL;
	mypoll.revents=0;
	numpoll=poll(&mypoll,1,0);
	if (numpoll<=0) return;


	USE_MSG_NOSIGNAL(numpoll=recv(t_sock,(void*)buf,sizeof(char),MSG_PEEK | MSG_NOSIGNAL));
	if (!numpoll)
	{

		CSocket_close(THIS);
		GB.Ref(THIS);
		GB.Post(CSocket_post_closed, (intptr_t)THIS);
		return;
	}


	GB.Raise(THIS, EVENT_Read, 0);


}
