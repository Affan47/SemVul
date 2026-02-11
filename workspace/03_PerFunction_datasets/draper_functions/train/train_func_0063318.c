calc_m_and_r (struct TREND1D_DATA *data, GMT_LONG n_data, double *model, GMT_LONG n_model, GMT_LONG m_type, double *grow)
{


	GMT_LONG	i;
	GMT_LONG j;
	for (i = 0; i < n_data; i++) {
		load_g_row(data[i].x, n_model, grow, m_type);
		data[i].m = 0.0;
		for (j = 0; j < n_model; j++) {
			data[i].m += model[j]*grow[j];
		}
		data[i].r = data[i].y - data[i].m;
	}
}
