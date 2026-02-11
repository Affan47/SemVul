lpsolve_affine_func (GString *dst, GnmCell *target, GnmSubSolver *ssol,
		     gnm_float cst, GSList *input_cells, GError **err)
{
	GSList *l, *ol;
	gboolean any = FALSE;
	gnm_float y;
	GSList *old_values = NULL;
	gboolean ok = TRUE;

	if (!target) {
		gnm_string_add_number (dst, cst);
		return TRUE;
	}

 	for (l = input_cells; l; l = l->next) {
	        GnmCell *cell = l->data;
		old_values = g_slist_prepend (old_values,
					      value_dup (cell->value));
		gnm_cell_set_value (cell, value_new_int (0));
		cell_queue_recalc (cell);
	}
	old_values = g_slist_reverse (old_values);

	gnm_cell_eval (target);
	y = cst + value_get_as_float (target->value);

 	for (l = input_cells; l; l = l->next) {
	        GnmCell *cell = l->data;
		gnm_float x;
		ok = gnm_solver_get_lp_coeff (target, cell, &x, err);
		if (!ok)
			goto fail;
		if (x == 0)
			continue;

		if (any) {
			if (x < 0)
				g_string_append (dst, " - ");
			else
				g_string_append (dst, " + ");
		} else {
			if (x < 0)
				g_string_append_c (dst, '-');
		}
		x = gnm_abs (x);

		if (x != 1) {
			gnm_string_add_number (dst, x);
			g_string_append_c (dst, ' ');
		}

		g_string_append (dst, lpsolve_var_name (ssol, cell));

		any = TRUE;
	}

	if (!any || y) {
		if (any) {
			g_string_append_c (dst, ' ');
			if (y > 0)
				g_string_append_c (dst, '+');
		}
		gnm_string_add_number (dst, y);
	}

fail:
 	for (l = input_cells, ol = old_values;
	     l;
	     l = l->next, ol = ol->next) {
	        GnmCell *cell = l->data;
		GnmValue *old = ol->data;
		gnm_cell_set_value (cell, old);
		cell_queue_recalc (cell);
	}
	g_slist_free (old_values);

	return ok;
}
