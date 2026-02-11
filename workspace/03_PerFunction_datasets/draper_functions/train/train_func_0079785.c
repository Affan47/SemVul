runtime_memequal(bool *eq, uintptr s, void *a, void *b)
{
	byte *ba, *bb, *aend;

	if(a == b) {
		*eq = 1;
		return;
	}
	ba = a;
	bb = b;
	aend = ba+s;
	while(ba != aend) {
		if(*ba != *bb) {
			*eq = 0;
			return;
		}
		ba++;
		bb++;
	}
	*eq = 1;
	return;
}
