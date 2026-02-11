bez_fact(int n)
{
	int idx;
	int product = 1;


	for(idx=1; idx<=n; idx++){
		product *= idx;
	}

	return product;
}
