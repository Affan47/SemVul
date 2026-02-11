cdb_make_add(struct cdb_make *c,char *key,unsigned int keylen,char *data,unsigned int datalen) {
    uint32 h, pos;
    int i , ch;

    pos = c->pos;
    cdbmake_pack(packbuf,(uint32) keylen);
    cdbmake_pack(packbuf + 4,(uint32) datalen);
    if (write(c->fd,packbuf,8) != 8)
	return -1;
    h = CDBMAKE_HASHSTART;
    for (i = 0;i < keylen;++i) {
      ch = key[i];
      h = cdbmake_hashadd(h,ch);
      if (write(c->fd, &key[i], 1) != 1)
          return -1;
    }
    for (i = 0;i < datalen;++i) {
      ch = data[i];
      if (write(c->fd, &data[i], 1) != 1)
          return -1;
    }
    if (!cdbmake_add(&c->cdbm,h,pos,malloc))
	return -1;
    pos = safeadd(pos,(uint32) 8);
    pos = safeadd(pos,(uint32) keylen);
    pos = safeadd(pos,(uint32) datalen);
    c->pos = pos;
    return 0;
}
