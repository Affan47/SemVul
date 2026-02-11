remove_path_prefix(const nstring& haystack, long count)
{
    size_t n;
    long slash = 0;

    trace(("remove_path_prefix(\"%s\", %ld)\n{\n", haystack.c_str(), count));

    if (count == 0)
    {
        trace(("return \"%s\";\n}\n", haystack.c_str()));
        return haystack;
    }

    for (n = 0; n < haystack.size(); ++n)
    {
        if (haystack[n] != '/')
            continue;


        if (n < (haystack.size() - 1) && haystack[n] == haystack[ n + 1 ])
            continue;
        ++slash;
        if (slash == count)
            break;
    }
    trace(("return \"%s\";\n}\n", haystack.c_str() + n + 1));
    return nstring(haystack.c_str() + n + 1, haystack.size() - n - 1);
}
