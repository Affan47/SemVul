mpz_get_64 (mpz_t a){
	if (mpz_fits_ulong_p (a)){
		return (uint64_t) mpz_get_ui(a);
	}
	uint64_t res = 0;
	if (sizeof(mp_limb_t) == 4){
		res = mpz_getlimbn (a, 1);
		res = (res << 32) | mpz_getlimbn(a, 0);
	} else {
		res = mpz_getlimbn (a, 0);
	}
	return res;
}
