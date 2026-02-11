isBin(const std::string& str)
{
    bool sign = str[0]=='-' || str[0]=='+';
    return((str.compare(sign?1:0, 2, "0b") == 0 || str.compare(sign?1:0, 2, "0B") == 0) && str.find_first_not_of("10bB", 1) == std::string::npos);
}
