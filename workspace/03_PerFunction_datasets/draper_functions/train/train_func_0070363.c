lz77_advance(struct LZ77InternalContext *st,
			 unsigned char c, int hash)
{
    int off;


    if (st->win[st->winpos].prev != INVALID) {
	st->win[st->win[st->winpos].prev].next = INVALID;
    } else if (st->win[st->winpos].hashval != INVALID) {
	st->hashtab[st->win[st->winpos].hashval].first = INVALID;
    }


    st->win[st->winpos].hashval = hash;
    st->win[st->winpos].prev = INVALID;
    off = st->win[st->winpos].next = st->hashtab[hash].first;
    st->hashtab[hash].first = st->winpos;
    if (off != INVALID)
	st->win[off].prev = st->winpos;
    st->data[st->winpos] = c;


    st->winpos = (st->winpos + 1) & (WINSIZE - 1);
}
