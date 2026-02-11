dvmax(DVECTOR x, long *index)
{
    long k;
    long ind;
    double max;

    ind = 0;
    max = x->data[ind];
    for (k = 1; k < x->length; k++) {
	if (max < x->data[k]) {
	    ind = k;
	    max = x->data[k];
	}
    }

    if (index != NULL) {
	*index = ind;
    }

    return max;
}
