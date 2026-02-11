_F_mpz_poly_normalise(F_mpz_poly_t poly)
{
   ulong length = poly->length;

	while ((length) && (!poly->coeffs[length - 1])) length--;

	poly->length = length;
}
