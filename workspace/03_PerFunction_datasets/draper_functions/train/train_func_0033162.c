is_equal(
    const boost::serialization::extended_type_info &rhs) const
{

    if(this == & rhs)
        return true;

    const char * l = get_key();
    BOOST_ASSERT(NULL != l);
    if(NULL == l)
        return false;
    const char * r = rhs.get_key();
    BOOST_ASSERT(NULL != r);
    if(NULL == r)
        return false;
    return 0 == std::strcmp(l, r);
}
