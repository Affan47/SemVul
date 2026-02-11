IdentSeqs(e_type E1, e_type E2)

{
	long	s;

	if(E1->n != E2->n) return FALSE;
	for(s=1; s<= (long) E1->n; s++){
		if(E1->X[s] != E2->X[s]) return FALSE;
	}
	return TRUE;
}
