booleanize_or_null()
    const
{
    trace(("%s\n", __PRETTY_FUNCTION__));


    rpt_value::pointer vp = arithmetic_or_null();
    if (vp)
        return rpt_value::booleanize(vp);


    struct table_t
    {
        const char *name;
        bool value;
    };
    static const table_t table[] =
    {
        { "false", false },
        { "no", false },
        { "true", true },
        { "yes", true },
    };
    nstring val = value.trim();
    for (const table_t *tp = table; tp < ENDOF(table); ++tp)
    {
        if (0 == strcasecmp(tp->name, val.c_str()))
            return rpt_value_boolean::create(tp->value);
    }


    return pointer();
}
