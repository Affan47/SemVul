mempool_dump(struct mempool *mp, int fd,
	     int (*serialize)(void *buf,
			      void *ptr, int count, int siz,
			      void *arg),
	     void *arg)
{
    int e;
    DPRINT(("\ndump: mem=%p\n", mp));
    e = mempool_dump_rec(mp, 0, mp->siz, fd, serialize, arg);
    DPRINT((" done\n"));
    return e;
}
