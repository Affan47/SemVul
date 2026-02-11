GetIsBumpMap(bool &ret) const
{
    if (!isValid()) return false;
    ret = isBump;
    return true;
}
