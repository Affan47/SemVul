iter_advance(cdb *c) {
	char buf[8];
	U32 klen, dlen;

	if (cdb_read(c, buf, 8, c->curpos) == -1) readerror();
	uint32_unpack(buf, &klen);
	uint32_unpack(buf + 4, &dlen);
	c->curpos += 8 + klen + dlen;
}
