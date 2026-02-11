getCurrentOption(OFCmdString &opt)
{
    if (OptionPosIterator != OptionPosList.end())
        return (opt = **OptionPosIterator).length() > 0;
    return OFFalse;
}
