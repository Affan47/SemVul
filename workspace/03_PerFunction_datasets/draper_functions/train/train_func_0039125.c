print_constraints(__isl_keep isl_basic_map *bmap,
	__isl_keep isl_space *dim, __isl_take isl_printer *p, int latex)
{
	int i;
	struct isl_vec *c;
	unsigned total = isl_basic_map_total_dim(bmap);

	c = isl_vec_alloc(bmap->ctx, 1 + total);
	if (!c)
		goto error;

	for (i = bmap->n_eq - 1; i >= 0; --i) {
		int l = isl_seq_last_non_zero(bmap->eq[i], 1 + total);
		if (l < 0) {
			if (i != bmap->n_eq - 1)
				p = isl_printer_print_str(p, s_and[latex]);
			p = isl_printer_print_str(p, "0 = 0");
			continue;
		}
		if (isl_int_is_neg(bmap->eq[i][l]))
			isl_seq_cpy(c->el, bmap->eq[i], 1 + total);
		else
			isl_seq_neg(c->el, bmap->eq[i], 1 + total);
		p = print_constraint(bmap, dim, p, c->el, l,
				    "=", i == bmap->n_eq - 1, latex);
	}
	for (i = 0; i < bmap->n_ineq; ++i) {
		int l = isl_seq_last_non_zero(bmap->ineq[i], 1 + total);
		int s;
		const char *op;
		if (l < 0)
			continue;
		s = isl_int_sgn(bmap->ineq[i][l]);
		if (s < 0)
			isl_seq_cpy(c->el, bmap->ineq[i], 1 + total);
		else
			isl_seq_neg(c->el, bmap->ineq[i], 1 + total);
		op = s < 0 ? s_le[latex] : s_ge[latex];
		p = print_constraint(bmap, dim, p, c->el, l,
					op, !bmap->n_eq && !i, latex);
	}

	isl_vec_free(c);

	return p;
error:
	isl_vec_free(c);
	isl_printer_free(p);
	return NULL;
}
