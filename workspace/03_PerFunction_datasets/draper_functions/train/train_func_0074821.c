is_set_prime(int *a) {
    while (*a) {
	if (!is_prime(*a))
	    return false;
	a++;
    }
    return true;
}
