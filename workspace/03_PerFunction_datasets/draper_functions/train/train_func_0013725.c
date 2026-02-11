real_can_shorten_arithmetic (enum machine_mode imode, enum machine_mode tmode)
{
  const struct real_format *tfmt, *ifmt;
  tfmt = REAL_MODE_FORMAT (tmode);
  ifmt = REAL_MODE_FORMAT (imode);


  return (ifmt->b == tfmt->b
	  && ifmt->p > 2 * tfmt->p
	  && ifmt->emin < 2 * tfmt->emin - tfmt->p - 2
	  && ifmt->emin < tfmt->emin - tfmt->emax - tfmt->p - 2
	  && ifmt->emax > 2 * tfmt->emax + 2
	  && ifmt->emax > tfmt->emax - tfmt->emin + tfmt->p + 2
	  && ifmt->round_towards_zero == tfmt->round_towards_zero
	  && (ifmt->has_sign_dependent_rounding
	      == tfmt->has_sign_dependent_rounding)
	  && ifmt->has_nans >= tfmt->has_nans
	  && ifmt->has_inf >= tfmt->has_inf
	  && ifmt->has_signed_zero >= tfmt->has_signed_zero
	  && !MODE_COMPOSITE_P (tmode)
	  && !MODE_COMPOSITE_P (imode));
}
