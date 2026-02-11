return_freelists(ptr_t *fl, ptr_t *gfl)
{
    int i;
    ptr_t q, *qptr;
    size_t nwords;

    for (i = 1; i < NFREELISTS; ++i) {
	nwords = i * (GRANULARITY/sizeof(word));
        qptr = fl + i;
	q = *qptr;
	if ((word)q >= HBLKSIZE) {
	  if (gfl[nwords] == 0) {
	    gfl[nwords] = q;
	  } else {

	    for (; (word)q >= HBLKSIZE; qptr = &(obj_link(q)), q = *qptr);
	    GC_ASSERT(0 == q);
	    *qptr = gfl[nwords];
	    gfl[nwords] = fl[i];
	  }
	}


	fl[i] = (ptr_t)HBLKSIZE;
    }
}
