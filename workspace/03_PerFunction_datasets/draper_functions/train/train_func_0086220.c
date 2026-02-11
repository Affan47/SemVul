comb_get_next_combination (int *vec, int len, int n)
{
	int i = len;
	int j;


	while (i > 0 && vec[i-1] == n-(len-i)) {
		i--;
	}
	if (i == 0) {
		return FALSE;
	} else {
		vec[i-1] ++;
		for (j = i+1; j <= len; j++)
			vec[j-1] = vec[j-2]+1;
	}
	return TRUE;
}
