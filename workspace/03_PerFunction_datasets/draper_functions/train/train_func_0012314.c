write()
{
    fileBuf.clear();
    if (!writeFileData())
        return false;
    if (!writeCentralDirectory())
        return false;
    return true;
}
