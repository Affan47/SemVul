main(void) {
    char array[9];
    int largest = 0;
    int i, n, temp;
    char c[9];
    for (n = 1; n < 10; n++) {


	for (i = 0; i < n; i++) {
	    c[i] = 0;
	    array[i] = i+1;
	}
	temp = check_array(array, n);
	if (temp > largest) {
	    largest = temp;
	}
	for (i = 1; i < n; ) {
	    if (c[i] < i) {
		int j = i % 2 ? c[i] : 0;
		temp = array[j];
		array[j] = array[i];
		array[i] = temp;
		c[i]++;
		i = 1;
		temp = check_array(array, n);
		if (temp > largest) {
		    largest = temp;
		}
	    } else {
		c[i] = 0;
		i++;
	    }
	}
    }
    printf("largest: %d\n", largest);
    return 0;
}
