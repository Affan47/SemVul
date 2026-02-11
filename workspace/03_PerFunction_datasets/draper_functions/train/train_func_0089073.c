title_filter(const string &title)
{
    string normtitle = string_normalize(title);
    size_t p = title.rfind("- ");
    if (p == string::npos)
        return normtitle;
    return string_normalize(title.substr(p));
}
