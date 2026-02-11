alloc(LEN len)
{
	HALF *hp;

	if (_math_abort_) {
		math_error("Calculation aborted");

	}
	hp = (HALF *) malloc((len+1) * sizeof(HALF));
	if (hp == 0) {
		math_error("Not enough memory");

	}
#ifdef ALLOCTEST
	++nalloc;
#endif
	return hp;
}
