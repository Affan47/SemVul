is_set(const nstring &name)
    const
{


    nstring lc_name(sanitize_name(name));
    nstring *value_p = database.query(lc_name);
    return (value_p != 0);
}
