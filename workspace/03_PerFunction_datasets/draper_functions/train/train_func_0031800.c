AllocBlastData (ml_state_t *msp, Addr_t sizeB)
{
    heap_t	    *heap = msp->ml_heap;
    int		    nWords = BYTES_TO_WORDS(sizeB);
    ml_val_t	    desc = MAKE_DESC(nWords, DTAG_raw32);
    ml_val_t	    res;


    if (sizeB < heap->allocSzB-(8*ONE_K)) {
	ML_AllocWrite (msp, 0, desc);
	res = ML_Alloc (msp, nWords);
	return res;
    }
    else {
	Die ("blasting out of %d bytes not supported yet!  Increase allocation arena size.", sizeB);
    }

}
