parse(std::string &string)
{
    std::stringstream ss;
    ss << string;
    bool error = false;
    Variant v = parseValue(ss, error);

    if(error)
        return Variant();

    return v;

}
