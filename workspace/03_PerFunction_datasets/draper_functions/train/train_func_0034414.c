getCurrentOption(const char *&opt)
{
    if (OptionPosIterator != OptionPosList.end())
        return (opt = (**OptionPosIterator).c_str())[0] != '\0';
    return OFFalse;
}
