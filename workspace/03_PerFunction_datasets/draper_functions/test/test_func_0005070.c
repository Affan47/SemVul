tchebyshev(double x, int o) {
	switch (o) {
	case 0: return   1;
	case 1: return   x;
	case 2: return   2.*pow(x, 2) - 1;
	case 3: return   4.*pow(x, 3) -   3*x;
	case 4: return   8.*pow(x, 4) -   8.*pow(x, 2) +   1;
	case 5: return  16.*pow(x, 5) -  20.*pow(x, 3) +   5.*x;
	case 6: return  32.*pow(x, 6) -  48.*pow(x, 4) +  18.*pow(x,2) -  1;
	case 7: return  64.*pow(x, 7) - 112.*pow(x, 5) +  56.*pow(x,3) -  7.*x;
	case 8: return 128.*pow(x, 8) - 256.*pow(x, 6) + 160.*pow(x,4) -  32.*pow(x,2) + 1;
	case 9: return 256.*pow(x, 9) - 576.*pow(x, 7) + 432.*pow(x,5) - 120.*pow(x,3) + 9.*x;
	}
	assert(0);
	return 0.0;
}
