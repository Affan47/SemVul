mono_return_int5 (int5 s5, int addend) {
	if (s5.f1 != 1) {
		fprintf(stderr, "mono_return_int5 s5.f1: got %d but expected %d\n", s5.f1, 1);
	}
	if (s5.f2 != 2) {
		fprintf(stderr, "mono_return_int5 s5.f2: got %d but expected %d\n", s5.f2, 2);
	}
	if (s5.f3 != 3) {
		fprintf(stderr, "mono_return_int5 s5.f3: got %d but expected %d\n", s5.f3, 3);
	}
	if (s5.f4 != 4) {
		fprintf(stderr, "mono_return_int5 s5.f4: got %d but expected %d\n", s5.f4, 4);
	}
	if (s5.f5 != 5) {
		fprintf(stderr, "mono_return_int5 s5.f5: got %d but expected %d\n", s5.f5, 5);
	}
	s5.f1+=addend; s5.f2+=addend; s5.f3+=addend; s5.f4+=addend; s5.f5+=addend;
	return s5;
}
