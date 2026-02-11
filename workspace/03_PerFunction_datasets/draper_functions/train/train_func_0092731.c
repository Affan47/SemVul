copy_periods_list (int *T0, const int *Ti)
{
    int j, ret = 1;

    for (j=0; j<=Ti[0] && ret; j++) {
	if (j > 1 && Ti[j] != Ti[j-1] + 1) {
	    ret = 0;
	} else {
	    T0[j] = Ti[j];
	}
    }

    return ret;
}
