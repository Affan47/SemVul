go_line_dash_get_sequence (GOLineDashType type, double scale)
{
	unsigned int i;
	GOLineDashSequence *sequence = NULL;
	GOLineDashDesc const *dash_desc;

	if ((unsigned)type >= G_N_ELEMENTS (line_dashes))
		return NULL;

	dash_desc = line_dashes[type].dash_desc;
	if (dash_desc != NULL) {
		sequence = g_new (GOLineDashSequence, 1);
		sequence->offset = 0.0;
		sequence->n_dash = dash_desc->n_dash;
		sequence->dash = g_new (double, sequence->n_dash);
		for (i = 0; i < sequence->n_dash; i++)
			sequence->dash[i] = scale * dash_desc->dash[i];
		sequence->ref_count = 1;
	}

	return sequence;
}
