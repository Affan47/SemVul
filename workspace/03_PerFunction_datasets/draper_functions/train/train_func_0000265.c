XML(const char *indent) const
{
    if (IsDefault())
        return "";
    char *value = g_markup_escape_text(StringValue(), -1);
    std::string str = (std::string)indent +
                      "<" + Name() + ">" + value + "</" + Name() + ">\n";
    g_free(value);
    return str;
}
