initialize(void)
{
    int i, j;

    natb = 0;
    for (i = 0; i < window.rows; i++) {
	for (j = 0; j < window.cols; j++) {
	    av(i, j) = window.ns_res * window.ew_res;
	    if (IScvNULL(i, j)) {
		natb++;
		G_set_d_null_value(&atbv(i, j), 1);
	    }
	    else {
		atbv(i, j) = -10.0;
	    }
	}
    }
}
