cosh(const RCP<const Basic> &arg)
{
    if (eq(arg, zero)) return one;
    if (is_a_Number(*arg) &&
        rcp_static_cast<const Number>(arg)->is_negative()) {
        return cosh(mul(minus_one, arg));
    }
    if (could_extract_minus(arg)) {
        return cosh(mul(minus_one, arg));
    }
    return rcp(new Cosh(arg));
}
