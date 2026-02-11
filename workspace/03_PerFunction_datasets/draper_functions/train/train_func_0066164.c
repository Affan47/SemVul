operator==(const TSrvOptInterfaceID &other) const
{
    if (DataLen != other.DataLen)
	return false;
    if (!memcmp(Data, other.Data, DataLen))
	return true;
    return false;
}
