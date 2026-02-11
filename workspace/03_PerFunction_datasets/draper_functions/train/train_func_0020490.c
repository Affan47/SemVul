nthroot_mod(const Ptr<RCP<const Integer>> &root, const RCP<const Integer> &a,
        const RCP<const Integer> &n, const RCP<const Integer> &mod)
{
    if (mod->as_mpz() <= 0) {
        return false;
    } else if (mod->as_mpz() == 1) {
        *root = integer(0);
        return true;
    }
    map_integer_uint prime_mul;
    prime_factor_multiplicities(prime_mul, *mod);
    std::vector<RCP<const Integer>> moduli;
    bool ret_val;
    mpz_class _mod;

    std::vector<RCP<const Integer>> rem;
    for (auto &it: prime_mul) {
        mpz_pow_ui(_mod.get_mpz_t(), it.first->as_mpz().get_mpz_t(), it.second);
        moduli.push_back(integer(_mod));
        ret_val = _nthroot_mod_prime_power(rem, a->as_mpz(), n->as_mpz(), it.first->as_mpz(), it.second, false);
        if(!ret_val) return false;
    }
    crt(root, rem, moduli);
    return true;
}
