parse(const wcstring &str)
{
    bool success = false;
    if (! success) success = try_parse_special(str);
    if (! success) success = try_parse_named(str);
    if (! success) success = try_parse_rgb(str);
    if (! success)
    {
        bzero(this->data.rgb, sizeof this->data.rgb);
        this->type = type_none;
    }
}
