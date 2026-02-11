gog_series_labels_get_position (GogSeriesLabels const *lbls)
{
	g_return_val_if_fail (GOG_IS_SERIES_LABELS (lbls), GOG_SERIES_LABELS_DEFAULT_POS);
	return (lbls->position == GOG_SERIES_LABELS_DEFAULT_POS)?
		lbls->default_pos: lbls->position;
}
