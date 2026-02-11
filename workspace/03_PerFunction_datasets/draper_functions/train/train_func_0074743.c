uncle_iter2(uncle *u, const char *k, const char *v)
{
	char name[256], addr[256];
	name[255] = addr[255] = 0;
	unsigned port = 0;
	int tcp = 0, ssl = 0, local = 0;
	sscanf(v, "%255[^/]/%255[^/]/%d/%u/%d/%d", name, addr, &local, &port, &tcp, &ssl);

	if (u->search.name[0] && strcmp(u->search.name, name))
		return 0;

	if ((u->search.tcp >= 0) && (u->search.tcp != tcp))
		return 1;

	if ((u->search.ssl >= 0) && (u->search.ssl != ssl))
		return 1;

	char tmpbuf[1024];
	sprintf(tmpbuf,
		"{\"$scope\":\"%s\",\"$unique\":%llu,\"$cmd\":\"+\",\"$name\":\"%s\",\"$port\":%u,\"$tcp\":%s,\"$ssl\":%s}\n",
			u->scope, (unsigned long long)u->unique, name, port, tcp?"true":"false", ssl?"true":"false");
	session_writemsg(u->search.s, tmpbuf);
	if (g_debug) printf("SND: %s", tmpbuf);
	return 1;
}
