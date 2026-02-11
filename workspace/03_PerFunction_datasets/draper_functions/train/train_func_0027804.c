is_canonical(const RCP<const Basic> &arg)
{

    if (is_a<Integer>(*arg) &&
            rcp_static_cast<const Integer>(arg)->is_zero())
        return false;

    RCP<const Integer> n;
    RCP<const Basic> r;
    bool b = get_pi_shift(arg, outArg(n), outArg(r));
    if (b)
        return false;
    return true;
}
