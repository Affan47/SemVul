setEndPointId(const unsigned int type, const unsigned int id)
{
    if (type == (unsigned int) VertID::src)
    {
        _srcId = id;
    }
    else
    {
        _dstId = id;
    }
}
