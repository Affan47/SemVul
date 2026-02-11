toString() const
{
    DOMString str = schemeStr;
    if (authority.size() > 0)
        {
        str.append("//");
        str.append(toStr(authority));
        }
    str.append(toStr(path));
    if (query.size() > 0)
        {
        str.append("?");
        str.append(toStr(query));
        }
    if (fragment.size() > 0)
        {
        str.append("#");
        str.append(toStr(fragment));
        }
    return str;
}
