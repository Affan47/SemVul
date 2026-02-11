stringize_or_null()
    const
{
    nstring s(ctime(&value), 24);
    return rpt_value_string::create(s);
}
