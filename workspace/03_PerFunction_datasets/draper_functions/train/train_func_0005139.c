compare(const Basic &o) const
{
    CSYMPY_ASSERT(is_a<ATan2>(o))
    const ATan2 &s = static_cast<const ATan2 &>(o);
    return div(num_, den_)->__cmp__(*div(s.num_, s.den_));
}
