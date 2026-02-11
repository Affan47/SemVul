X509_PURPOSE_get_by_id(int purpose)
{
	X509_PURPOSE tmp;
	int idx;
	if((purpose >= X509_PURPOSE_MIN) && (purpose <= X509_PURPOSE_MAX))
		return purpose - X509_PURPOSE_MIN;
	tmp.purpose = purpose;
	if(!xptable) return -1;
	idx = sk_X509_PURPOSE_find(xptable, &tmp);
	if(idx == -1) return -1;
	return idx + X509_PURPOSE_COUNT;
}
