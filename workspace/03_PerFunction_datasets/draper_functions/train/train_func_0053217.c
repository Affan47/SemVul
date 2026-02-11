ec2n_setraw(struct group *grp, ec2np_ptr out, u_int8_t *s, int l)
{
	int             len, bytes, i, j;
	b2n_ptr         outx = out->x;
	CHUNK_TYPE      tmp;

	len = (CHUNK_BYTES - 1 + l) / CHUNK_BYTES;
	if (b2n_resize(outx, len))
		return -1;

	bytes = ((l - 1) % CHUNK_BYTES) + 1;

	for (i = len - 1; i >= 0; i--) {
		tmp = 0;
		for (j = (i == len - 1 ? bytes : CHUNK_BYTES); j > 0; j--) {
			tmp <<= 8;
			tmp |= *s++;
		}
		outx->limp[i] = tmp;
	}
	return 0;
}
