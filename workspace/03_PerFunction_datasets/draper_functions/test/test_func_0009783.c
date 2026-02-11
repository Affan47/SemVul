mono_return_double1 (double1 s1, int addend) {
	if (s1.f1 != 1) {
		fprintf(stderr, "mono_return_double1 s1.f1: got %f but expected %d\n", s1.f1, 1);
	}
	s1.f1+=addend;
	return s1;
}
