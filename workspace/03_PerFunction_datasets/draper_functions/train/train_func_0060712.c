gnumeric_duration (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
        GDate     nSettle, nMat;
	gnm_float fCoup, fYield;
        gnm_float fNumOfCoups;
	GoCouponConvention conv;

	conv.date_conv = workbook_date_conv (ei->pos->sheet->workbook);
	conv.eom = TRUE;

	fCoup      = value_get_as_float (argv[2]);
	fYield     = value_get_as_float (argv[3]);
	conv.freq  = value_get_freq (argv[4]);
        conv.basis = value_get_basis (argv[5], GO_BASIS_MSRB_30_360);

        if (!datetime_value_to_g (&nSettle, argv[0], conv.date_conv) ||
	    !datetime_value_to_g (&nMat, argv[1], conv.date_conv) ||
	    !is_valid_basis (conv.basis) ||
	    !is_valid_freq (conv.freq))
		return value_new_error_NUM (ei->pos);

	fNumOfCoups = coupnum (&nSettle, &nMat, &conv);
	return get_duration (&nSettle, &nMat, fCoup, fYield, conv.freq,
			     conv.basis, fNumOfCoups);
}
