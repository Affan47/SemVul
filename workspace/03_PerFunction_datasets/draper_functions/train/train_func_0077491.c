set_query_if_empty(const nstring &s)
{
    assert(s.c_str()[0] != '?');
    if (query.empty())
	query = "?" + s;
}
