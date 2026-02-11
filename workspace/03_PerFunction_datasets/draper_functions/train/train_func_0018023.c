value(vector<string> &b) const
{
    if (_var->type() == dods_str_c || _var->type() == dods_url_c)
        b = d_str;
}
