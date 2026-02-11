mono_return_sbyte11 (sbyte11 s11, int addend) {
	if (s11.f1 != 1) {
		fprintf(stderr, "mono_return_sbyte11 s11.f1: got %d but expected %d\n", s11.f1, 1);
	}
	if (s11.f2 != 2) {
		fprintf(stderr, "mono_return_sbyte11 s11.f2: got %d but expected %d\n", s11.f2, 2);
	}
	if (s11.f3 != 3) {
		fprintf(stderr, "mono_return_sbyte11 s11.f3: got %d but expected %d\n", s11.f3, 3);
	}
	if (s11.f4 != 4) {
		fprintf(stderr, "mono_return_sbyte11 s11.f4: got %d but expected %d\n", s11.f4, 4);
	}
	if (s11.f5 != 5) {
		fprintf(stderr, "mono_return_sbyte11 s11.f5: got %d but expected %d\n", s11.f5, 5);
	}
	if (s11.f6 != 6) {
		fprintf(stderr, "mono_return_sbyte11 s11.f6: got %d but expected %d\n", s11.f6, 6);
	}
	if (s11.f7 != 7) {
		fprintf(stderr, "mono_return_sbyte11 s11.f7: got %d but expected %d\n", s11.f7, 7);
	}
	if (s11.f8 != 8) {
		fprintf(stderr, "mono_return_sbyte11 s11.f8: got %d but expected %d\n", s11.f8, 8);
	}
	if (s11.f9 != 9) {
		fprintf(stderr, "mono_return_sbyte11 s11.f9: got %d but expected %d\n", s11.f9, 9);
	}
	if (s11.f10 != 10) {
		fprintf(stderr, "mono_return_sbyte11 s11.f10: got %d but expected %d\n", s11.f10, 10);
	}
	if (s11.f11 != 11) {
		fprintf(stderr, "mono_return_sbyte11 s11.f11: got %d but expected %d\n", s11.f11, 11);
	}
	s11.f1+=addend; s11.f2+=addend; s11.f3+=addend; s11.f4+=addend; s11.f5+=addend; s11.f6+=addend; s11.f7+=addend; s11.f8+=addend; s11.f9+=addend; s11.f10+=addend; s11.f11+=addend;
	return s11;
}
