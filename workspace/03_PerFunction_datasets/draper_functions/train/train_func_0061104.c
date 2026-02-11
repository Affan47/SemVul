BN_MONT_CTX_copy(BN_MONT_CTX *to, BN_MONT_CTX *from)
	{
	if (to == from) return(to);

	if (!BN_copy(&(to->RR),&(from->RR))) return NULL;
	if (!BN_copy(&(to->N),&(from->N))) return NULL;
	if (!BN_copy(&(to->Ni),&(from->Ni))) return NULL;
	to->ri=from->ri;
	to->n0[0]=from->n0[0];
	to->n0[1]=from->n0[1];
	return(to);
	}
