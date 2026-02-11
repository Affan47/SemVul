compare(const Basic &o) const
{
    CSYMPY_ASSERT(is_a<LeviCivita>(o))
    const LeviCivita &s = static_cast<const LeviCivita &>(o);

    if (arg_.size() != s.arg_.size())
        return (arg_.size() < s.arg_.size()) ? -1 : 1;
    return vec_basic_compare(arg_, s.arg_);
}
