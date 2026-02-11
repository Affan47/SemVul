modnn(RS *rs, int x){
	while (x >= rs->nn) {
		x -= rs->nn;
		x = (x >> rs->mm) + (x & rs->nn);
	}
	return x;
}
