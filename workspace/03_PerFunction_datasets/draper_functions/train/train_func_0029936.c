mpz_normalize(mpz_ptr z)
{
	int32_t j;

	if (!z->a)
		return;
	j = z->a-1;
	while(j >= 0) {
		if (z->d[j])
			break;
		j--;
	}
	z->l = j+1;
	if (z->l == 0)
		z->s = 0;
}
