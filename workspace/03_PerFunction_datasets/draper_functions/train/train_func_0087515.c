hex2unsigned(const std::string& str)
{
    unsigned int r = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        r = r * 16 + str[i] - 48 - ((str[i] >= 'A') ? 7 : 0) - ((str[i] >= 'a') ? 32 : 0);
    }
    return r;
}
