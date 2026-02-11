FLAC__window_tukey(FLAC__real *window, const FLAC__int32 L, const FLAC__real p)
{
	if (p <= 0.0)
		FLAC__window_rectangle(window, L);
	else if (p >= 1.0)
		FLAC__window_hann(window, L);
	else {
		const FLAC__int32 Np = (FLAC__int32)(p / 2.0f * L) - 1;
		FLAC__int32 n;

		FLAC__window_rectangle(window, L);

		if (Np > 0) {
			for (n = 0; n <= Np; n++) {
				window[n] = (FLAC__real)(0.5f - 0.5f * cos(M_PI * n / Np));
				window[L-Np-1+n] = (FLAC__real)(0.5f - 0.5f * cos(M_PI * (n+Np) / Np));
			}
		}
	}
}
