srcdkfGetVariance(srcdkf_t *f, float32_t *q) {
	float32_t *Sx = f->Sx.pData;
	int i;


	if (q)
		for (i = 0; i < f->S; i++) {
			q[i] = Sx[i*f->S + i];
			q[i] = q[i]*q[i];
		}
}
