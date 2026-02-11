smallFib(double n) {
	if ( n > 1481 ) {
		std::cerr << "use getFib() for n=" << n << std::endl;
		return(-1);
	}
	double fib;
	double phi = (1+sqrt(5))/2;


	fib = (pow(phi,n) - pow(1-phi,n) ) / sqrt(5);
	return fib;
}
