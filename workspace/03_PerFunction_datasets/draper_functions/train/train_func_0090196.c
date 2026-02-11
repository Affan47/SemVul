comp_row_free (CompRow *row)
{
	if (row->values) {
		gint i;
		for (i = 0; i < row->size; i++) {
			if (row->values [i] && (row->values [i] != NON_COMP_VALUE))
				gda_value_free (row->values [i]);
		}
		g_free (row->values);
	}
	g_free (row);
}
