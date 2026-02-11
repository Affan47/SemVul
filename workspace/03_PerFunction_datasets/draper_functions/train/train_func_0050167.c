reseed(FState * st)
{
    unsigned	k;
    unsigned	n;
    MD_CTX		key_md;
    unsigned char	buf[BLOCK];


    st->pool0_bytes = 0;


    n = ++st->reseed_count;


    md_init(&key_md);
    for (k = 0; k < NUM_POOLS; k++)
    {
	md_result(&st->pool[k], buf);
	md_update(&key_md, buf, BLOCK);

	if (n & 1 || !n)
	    break;
	n >>= 1;
    }


    md_update(&key_md, st->key, BLOCK);


    md_update(&key_md, (const unsigned char *)&st->pid, sizeof(st->pid));


    md_result(&key_md, st->key);


    ciph_init(&st->ciph, st->key, BLOCK);

    memset(&key_md, 0, sizeof(key_md));
    memset(buf, 0, BLOCK);
}
