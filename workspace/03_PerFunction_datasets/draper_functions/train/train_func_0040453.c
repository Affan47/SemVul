expand_as_exp() const
{
    RCP<const Basic> pos_exp = exp(get_arg());
    RCP<const Basic> neg_exp = exp(mul(minus_one, get_arg()));
    return div(sub(pos_exp, neg_exp), add(pos_exp, neg_exp));
}
