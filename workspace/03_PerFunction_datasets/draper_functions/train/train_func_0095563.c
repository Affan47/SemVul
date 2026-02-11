setBaudRate(BaudRate r, FlowControl i, FlowControl o)
{
    iFlow = i;
    oFlow = o;
    rate = r;
    if (server.setBaudRate(r,i,o)) {
	if (conf.baudRateDelay)
	    pause(conf.baudRateDelay);
	return (true);
    } else
	return (false);
}
