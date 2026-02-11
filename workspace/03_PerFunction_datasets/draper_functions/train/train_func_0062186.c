cb_sylk_write_cell (GnmCellIter const *iter, SylkWriter *state)
{
	GnmValue const *v;
	GnmExprTop const *texpr;
	GnmExprArrayCorner const *array;

	if (iter->pp.eval.row != state->cur_row)
		gsf_output_printf (state->output, "C;Y%d;X%d",
			(state->cur_row = iter->pp.eval.row) + 1,
			iter->pp.eval.col + 1);
	else
		gsf_output_printf (state->output, "C;X%d",
			iter->pp.eval.col + 1);

	if (NULL != (v = iter->cell->value)) {
		if (VALUE_IS_STRING (v)) {
			gsf_output_write (state->output, 3, ";K\"");
			sylk_write (state, v->v_str.val->str);
			gsf_output_write (state->output, 1, "\"");
		} else if (VALUE_IS_NUMBER (v) || VALUE_IS_ERROR (v)) {
			GString *res = g_string_sized_new (10);
			value_get_as_gstring (v, res, state->convs);
			gsf_output_write (state->output, 2, ";K");
			gsf_output_write (state->output, res->len, res->str);
			g_string_free (res, TRUE);
		}
	}

	if (NULL != (texpr = iter->cell->base.texpr)) {
		if (NULL != (array = gnm_expr_top_get_array_corner (texpr))) {
			gsf_output_printf (state->output, ";R%d;C%d;M",
				iter->pp.eval.row + array->rows,
				iter->pp.eval.col + array->cols);
		} else if (gnm_expr_top_is_array_elem (texpr, NULL, NULL)) {
			gsf_output_write (state->output, 2, ";I");
			texpr = NULL;
		} else
			gsf_output_write (state->output, 2, ";E");

		if (texpr != NULL) {
			GnmConventionsOut out;
			out.accum = g_string_new (NULL);
			out.pp    = &iter->pp;
			out.convs = state->convs;
			gnm_expr_top_as_gstring (texpr, &out);
			sylk_write (state, out.accum->str);
			g_string_free (out.accum, TRUE);
		}
	}
	gsf_output_write (state->output, 2, "\r\n");
	return NULL;
}
