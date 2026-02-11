perfect_power(const Integer &n)
{
    return mpz_perfect_power_p(n.as_mpz().get_mpz_t());
}
