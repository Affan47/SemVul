matrix_max(const EST_IMatrix &a)
{
    int i, j;
    int v = INT_MIN;

    for (i = 0; i < a.num_rows(); ++i)
	for (j = 0; j < a.num_columns(); ++j)
	    if (a.a_no_check(i, j) > v)
		v = a.a_no_check(i, j);

    return v;
}
