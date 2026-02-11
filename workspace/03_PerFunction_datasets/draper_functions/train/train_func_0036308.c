healpix_decompose_xyl(int64_t finehp,
						   int* pbighp, int* px, int* py,
						   int Nside) {
	int64_t hp;
	int64_t ns2 = (int64_t)Nside * (int64_t)Nside;
	assert(Nside > 0);
	assert(finehp < (12L * ns2));
	assert(finehp >= 0);
	if (pbighp) {
		int bighp   = finehp / ns2;
		assert(bighp >= 0);
		assert(bighp < 12);
		*pbighp = bighp;
	}
	hp = finehp % ns2;
	if (px) {
		*px = hp / Nside;
		assert(*px >= 0);
		assert(*px < Nside);
	}
	if (py) {
		*py = hp % Nside;
		assert(*py >= 0);
		assert(*py < Nside);
	}
}
