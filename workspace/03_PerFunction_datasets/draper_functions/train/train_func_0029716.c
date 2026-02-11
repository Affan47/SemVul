setupHostModem(const fxStr& s)
{
    u_int pos = s.next(0, '@');
    if (pos != s.length()) {
	modem = s.head(pos);
	host = s.tail(s.length() - (pos+1));
    } else
	host = s;
    pos = host.next(0, ':');
    if (pos != host.length()) {
	port = atoi(host.tail(host.length() - (pos+1)));
	host.resize(pos);
    }
}
