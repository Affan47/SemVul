is_canonical(const RCP<const Basic> &arg,
        const vec_basic &x) const
{

    for(auto &a: x)
        if (!is_a<Symbol>(*a)) return false;
    if (is_a<FunctionSymbol>(*arg)) {
        RCP<const Symbol> s = rcp_static_cast<const Symbol>(x[0]);
        RCP<const FunctionSymbol> f = rcp_static_cast<const FunctionSymbol>(arg);
        bool found_s = false;


        for (auto &a : f->get_args()) {
            if (eq(a, s)) {
                if(found_s) {
                    return false;
                } else {
                    found_s = true;
                }
            } else if (neq(a->diff(s), zero)) {
                return false;
            }
        }
        return found_s;
    } else if (is_a<Abs>(*arg)) {
        return true;
    } else if (is_a<FunctionWrapper>(*arg)) {
        return true;
    }
    return false;
}
