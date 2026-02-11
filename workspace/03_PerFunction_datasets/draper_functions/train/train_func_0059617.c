test_prime_factor_multiplicities()
{
    RCP<const Integer> i2 = integer(2);
    RCP<const Integer> i3 = integer(3);
    RCP<const Integer> i6 = integer(6);
    RCP<const Integer> i12 = integer(12);
    RCP<const Integer> i36 = integer(36);
    RCP<const Integer> i125 = integer(125);
    RCP<const Integer> i2357 = integer(2357);

    _test_prime_factor_multiplicities(i2);
    _test_prime_factor_multiplicities(i3);
    _test_prime_factor_multiplicities(i6);
    _test_prime_factor_multiplicities(i12);
    _test_prime_factor_multiplicities(i36);
    _test_prime_factor_multiplicities(i125);
    _test_prime_factor_multiplicities(i2357);
}
