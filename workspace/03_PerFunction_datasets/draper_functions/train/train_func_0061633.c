getCurrentArg(OFCmdString &arg)
{
    if (ArgumentIterator != ArgumentList.end())
        return !(arg = *ArgumentIterator).empty();
    return OFFalse;

}
