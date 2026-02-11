main (int argc, char* argv[])
{
	for (int i = 1; i < argc; i++) {
		const char * arg = argv[i];
		try {

			cl_R x = arg;

			if (minusp(x)) {
				cout << '-';
				x = -x;
			}
			cout << "[";
			const char* separator = "; ";
			for (;;) {

			 	cl_R_div_t x_split = floor2(x);
				cout << x_split.quotient;
				x = x_split.remainder;
				if (zerop(x))
					break;
				cout << separator;
				separator = ", ";

				x = recip(x);
			}
			cout << ']' << endl;
		} catch ( const runtime_exception& ) {}
	}
}
