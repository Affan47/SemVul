cast_encrypt(cast_key* key, u_int8_t* inblock, u_int8_t* outblock)
{
u_int32_t t, l, r;


	l = ((u_int32_t)inblock[0] << 24) | ((u_int32_t)inblock[1] << 16) |
	 ((u_int32_t)inblock[2] << 8) | (u_int32_t)inblock[3];
	r = ((u_int32_t)inblock[4] << 24) | ((u_int32_t)inblock[5] << 16) |
	 ((u_int32_t)inblock[6] << 8) | (u_int32_t)inblock[7];

	F1(l, r,  0);
	F2(r, l,  1);
	F3(l, r,  2);
	F1(r, l,  3);
	F2(l, r,  4);
	F3(r, l,  5);
	F1(l, r,  6);
	F2(r, l,  7);
	F3(l, r,  8);
	F1(r, l,  9);
	F2(l, r, 10);
	F3(r, l, 11);

	if (key->rounds > 12) {
		F1(l, r, 12);
		F2(r, l, 13);
		F3(l, r, 14);
		F1(r, l, 15);
	}

	outblock[0] = U8a(r);
	outblock[1] = U8b(r);
	outblock[2] = U8c(r);
	outblock[3] = U8d(r);
	outblock[4] = U8a(l);
	outblock[5] = U8b(l);
	outblock[6] = U8c(l);
	outblock[7] = U8d(l);

	t = l = r = 0;
}
