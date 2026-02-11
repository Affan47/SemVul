scavenge_large_srt_bitmap( StgLargeSRT *large_srt )
{
    nat i, b, size;
    StgWord bitmap;
    StgClosure **p;

    b = 0;
    bitmap = large_srt->l.bitmap[b];
    size   = (nat)large_srt->l.size;
    p      = (StgClosure **)large_srt->srt;
    for (i = 0; i < size; ) {
	if ((bitmap & 1) != 0) {
	    evacuate(p);
	}
	i++;
	p++;
	if (i % BITS_IN(W_) == 0) {
	    b++;
	    bitmap = large_srt->l.bitmap[b];
	} else {
	    bitmap = bitmap >> 1;
	}
    }
}
