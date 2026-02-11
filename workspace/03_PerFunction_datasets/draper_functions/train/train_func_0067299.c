in_group(double att, float *group, int r)
{
    register int i;


    for (i = 1; i < recl_count[r]; i++) {


	if (-999 == *(group + i)) {
	    if (*(group + i) &&
		*(group + i - 1) <= att && att <= *(group + i + 1))
		return 1;
	    else
		i++;
	}


	else if ((double)*(group + i) == att) {
	    return 1;
	}
    }

    return 0;
}
