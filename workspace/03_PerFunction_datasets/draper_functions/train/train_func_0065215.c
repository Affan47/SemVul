is_canonical(const RCP<const Number> &coef,
        const map_basic_basic& dict)
{
    if (coef == null) return false;

    if (coef->is_zero())
        return false;
    if (dict.size() == 0) return false;
    if (dict.size() == 1) {

        if (coef->is_one()) return false;
    }

    for (auto &p: dict) {
        if (p.first == null) return false;
        if (p.second == null) return false;


        if ((is_a<Integer>(*p.first) || is_a<Rational>(*p.first))
            && is_a<Integer>(*p.second))
            return false;

        if (is_a<Integer>(*p.first) &&
                rcp_static_cast<const Integer>(p.first)->is_zero())
            return false;

        if (is_a<Integer>(*p.first) &&
                rcp_static_cast<const Integer>(p.first)->is_one())
            return false;

        if (is_a<Integer>(*p.second) &&
                rcp_static_cast<const Integer>(p.second)->is_zero())
            return false;


        if (is_a<Mul>(*p.first))
            return false;


        if (is_a<Pow>(*p.first))
            return false;
    }
    return true;
}
