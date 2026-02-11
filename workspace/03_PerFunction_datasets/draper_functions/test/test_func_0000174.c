getModemLine(char buf[], u_int bufSize, long ms)
{
    int n = server.getModemLine(buf, bufSize, ms);
    if (n > 0)
	trimModemLine(buf, n);
    return (n);
}
