gog_series1_5d_dim_changed (GogSeries *series, int dim_i)
{
	if (dim_i == 0)
		GOG_SERIES1_5D (series)->index_changed = TRUE;
}
