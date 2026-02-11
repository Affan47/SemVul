gnumeric_yieldmat (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
        GDate     nSettle, nMat, nIssue;
	gnm_float fRate, fPrice;
	gint      basis;
	GODateConventions const *date_conv =
		workbook_date_conv (ei->pos->sheet->workbook);

	fRate      = value_get_as_float (argv[3]);
	fPrice     = value_get_as_float (argv[4]);
        basis      = value_get_basis (argv[5], GO_BASIS_MSRB_30_360);

        if (!is_valid_basis (basis) ||
	    fRate < 0 ||
	    !datetime_value_to_g (&nSettle, argv[0], date_conv) ||
	    !datetime_value_to_g (&nMat, argv[1], date_conv) ||
	    !datetime_value_to_g (&nIssue, argv[2], date_conv))
		return value_new_error_NUM (ei->pos);

	return get_yieldmat (&nSettle, &nMat, &nIssue, fRate, fPrice, basis);
}
