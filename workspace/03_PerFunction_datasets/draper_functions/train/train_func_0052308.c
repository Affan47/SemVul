compress_big(const unsigned char *data, const sph_u64 h[16], sph_u64 dh[16])
{
#if SPH_LITTLE_FAST
#define M(x)    sph_dec64le_aligned(data + 8 * (x))
#else
	sph_u64 mv[16];

	mv[ 0] = sph_dec64le_aligned(data +   0);
	mv[ 1] = sph_dec64le_aligned(data +   8);
	mv[ 2] = sph_dec64le_aligned(data +  16);
	mv[ 3] = sph_dec64le_aligned(data +  24);
	mv[ 4] = sph_dec64le_aligned(data +  32);
	mv[ 5] = sph_dec64le_aligned(data +  40);
	mv[ 6] = sph_dec64le_aligned(data +  48);
	mv[ 7] = sph_dec64le_aligned(data +  56);
	mv[ 8] = sph_dec64le_aligned(data +  64);
	mv[ 9] = sph_dec64le_aligned(data +  72);
	mv[10] = sph_dec64le_aligned(data +  80);
	mv[11] = sph_dec64le_aligned(data +  88);
	mv[12] = sph_dec64le_aligned(data +  96);
	mv[13] = sph_dec64le_aligned(data + 104);
	mv[14] = sph_dec64le_aligned(data + 112);
	mv[15] = sph_dec64le_aligned(data + 120);
#define M(x)    (mv[x])
#endif
#define H(x)    (h[x])
#define dH(x)   (dh[x])

	FOLDb;

#undef M
#undef H
#undef dH
}
