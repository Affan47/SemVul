gnm_sort_contents (GnmSortData *data, GOCmdContext *cc)
{
	ColRowInfo const *cra;
	SortDataPerm *perm;
	int length, real_length, i, cur, *iperm, *real;
	int const first = data->top ? data->range->start.row : data->range->start.col;

	length = gnm_sort_data_length (data);
	real_length = 0;


	real = g_new (int, length);
	for (i = 0; i < length; i++) {
		cra = data->top
			? sheet_row_get (data->sheet, first + i)
			: sheet_col_get (data->sheet, first + i);

		if (cra && !cra->visible) {
			real[i] = -1;
		} else {
			real[i] = i;
			real_length++;
		}
	}

	cur = 0;
	perm = g_new (SortDataPerm, real_length);
	for (i = 0; i < length; i++) {
		if (real[i] != -1) {
			perm[cur].index = i;
			perm[cur].data = data;
			cur++;
		}
	}

	if (real_length > 1) {
		if (data->locale) {
			char *old_locale
				= g_strdup (go_setlocale (LC_ALL, NULL));
			go_setlocale (LC_ALL, data->locale);

			qsort (perm, real_length, sizeof (SortDataPerm),
			       g_str_has_prefix
			       (old_locale, data->locale)
			       ? sort_qsort_compare
			       : sort_qsort_compare_in_locale);

			go_setlocale (LC_ALL, old_locale);
			g_free (old_locale);
		} else
			qsort (perm, real_length, sizeof (SortDataPerm),
			       sort_qsort_compare);
	}

	cur = 0;
	iperm = g_new (int, length);
	for (i = 0; i < length; i++) {
		if (real[i] != -1) {
			iperm[i] = perm[cur].index;
			cur++;
		} else {
			iperm[i] = i;
		}
	}
	g_free (perm);
	g_free (real);

	sort_permute (data, iperm, length, cc);


	sheet_region_queue_recalc (data->sheet, data->range);
	sheet_flag_status_update_range (data->sheet, data->range);
	sheet_range_calc_spans (data->sheet, data->range,
				data->retain_formats ? GNM_SPANCALC_RENDER : GNM_SPANCALC_RE_RENDER);
	sheet_redraw_all (data->sheet, FALSE);

	return iperm;
}
