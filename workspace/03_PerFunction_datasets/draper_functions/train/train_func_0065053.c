char_erasemap(int fd, int id)
{
	int i;

	for(i = 0; i < MAX_MAP_SERVERS; i++) {
		int dfd = server_fd[i];
		if(dfd >= 0 && i != id) {
			WFIFORESERVE(dfd, server[id].map_num * 16 + 12);
			WFIFOW(dfd, 0) = 0x2b16;
			WFIFOW(dfd, 2) = server[id].map_num * 16 + 12;
			WFIFOL(dfd, 4) = server[id].ip;
			WFIFOW(dfd, 8) = server[id].port;
			WFIFOW(dfd,10) = server[id].map_num;
			memcpy(WFIFOP(dfd,12), server[id].map, 16 * server[id].map_num);
			WFIFOSET(dfd, WFIFOW(dfd,2));
		}
	}
	printf("char: map erase: id = %d, tag = %s (%d maps)\n", id, server[id].tag, server[id].map_num);

	aFree(server[id].map);
	server[id].map = NULL;
	server[id].map_num = 0;

	return 0;
}
