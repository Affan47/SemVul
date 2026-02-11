__str__() const
{
    std::ostringstream o;
    o << "zeta(" << *s_ ;
    if (neq(a_, one))
        o << ", " << *a_;
    o << ")";
    return o.str();
}
