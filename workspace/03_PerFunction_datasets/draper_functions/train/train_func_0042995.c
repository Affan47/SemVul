get_unix_ifaces()
{
	QList<UnixIface> out = get_sioc_ifaces();
#ifdef Q_OS_LINUX
	out += get_linux_ipv6_ifaces();
#endif
	return out;
}
