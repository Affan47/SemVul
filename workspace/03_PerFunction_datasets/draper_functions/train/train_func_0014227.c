vectorNormalize(float32_t *v, int n) {
	float32_t t;
	int i;

	t = 0.0f;
	for (i = 0; i < n; i++) {
		t += v[i] * v[i];
	}

	t = __sqrtf(t);

	if (t > 1e-6f) {
		t = 1.0f / t;
		for (i = 0; i < n; i++) {
			v[i] *= t;
		}
	} else {
		for (i = 0; i < n; i++) {
			v[i] *= 0.0f;
		}
	}
}
