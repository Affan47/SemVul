as_coef_term(const RCP<const Basic> &self,
        const Ptr<RCP<const Number>> &coef, const Ptr<RCP<const Basic>> &term)
{
    if (is_a<Mul>(*self)) {
        *coef = (rcp_static_cast<const Mul>(self))->coef_;
        *term = Mul::from_dict(one, (rcp_static_cast<const Mul>(self))->dict_);
    } else if (is_a_Number(*self)) {
        *coef = rcp_static_cast<const Number>(self);
        *term = one;
    } else {
        *coef = one;
        *term = self;
    }
}
