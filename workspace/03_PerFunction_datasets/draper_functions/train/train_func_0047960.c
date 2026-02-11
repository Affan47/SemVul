make_llogin_connection(int fd, const char *service, const char *rnode, const char *port,
				      const char *localport, const char *password, bool queued)
{
    int ret;
    int connid;

    connid = make_connection(fd, service, rnode, port, localport, password, queued);
    if (connid < 0)
	return connid;

    debuglog(("lloginSession for %s has connid %d\n", service, connid));

    ret = connections[connid]->create_llogin_session(fd, service, port, localport, password);


    deleted_session s(LLOGIN_SOCKET, 0, 0, fd);
    dead_session_list.push_back(s);

    return ret;
}
