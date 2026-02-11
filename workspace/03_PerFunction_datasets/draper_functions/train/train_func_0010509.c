is_bouncy(int n) {
    bool up = false, down = false;
    int lasti = n % 10;
    n = n/10;
    while(n) {
	int i = n % 10;
	n = n/10;
	if (i > lasti)
	    up = true;
	if (i < lasti)
	    down = true;
	if (up && down)
	    return true;
	lasti = i;
    }
    return false;
}
