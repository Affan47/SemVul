HexForm2(int x) const {


	x += 48;
	if (x >= 58 && x <= 63) x += 39;

	return ( (char)x );
}
