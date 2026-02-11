count(int n) {
    int c = 0;
    if (n == 1000)
	return 11;
    if (n < 10)
	return count_ones(n);
    if (n < 20)
	return count_teens(n);


    if (n / 100) {
	c += count_ones(n / 100);
	c += 7;
	n -= ((n/100)*100);
	if (n) {
	    c += 3;
	}
    }


    if (n / 10) {
	if (n < 20) {
	    c += count_teens(n);
	    n = 0;
	} else {
	    c += count_tens(n / 10);
	    n -= ((n/10)*10);
	}
    }


    if (n) {
	c += count_ones(n);
    }
    return c;
}
