SHA512_Init(SHA512_State *s) {
    int i;
    SHA512_Core_Init(s);
    s->blkused = 0;
    for (i = 0; i < 4; i++)
	s->len[i] = 0;
}
