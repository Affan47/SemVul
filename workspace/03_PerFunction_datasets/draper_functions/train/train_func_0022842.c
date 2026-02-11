initConnectEvent()
{
	pEventLoop->addEventListener(sSocket.getFd(), EV_IO_ALL, EV_IO_CB(this, Connection::onConnect), NULL);
	if(nTimeout){
		nTimerId = pEventLoop->setTimer(nTimeout, EV_TIMER_CB(this, Connection::onTimeout));
	}
}
