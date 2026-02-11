is_palindrome_d(int n) {
    int n_digits = 0;
    int temp = n;
    int i,j;
    while (temp) {
	n_digits++;
	temp /= 10;
    }
    i = 0;
    j = n_digits-1;
    while (i < j) {
	if (nth_digit(i,n) != nth_digit(j,n)) {
	    return 0;
	}
	i++;
	j--;
    }
    return 1;
}
