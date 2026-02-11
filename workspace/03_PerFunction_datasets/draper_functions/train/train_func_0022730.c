DoLayoutAdaptation()
{
    if (GetLayoutAdapter())
        return GetLayoutAdapter()->DoLayoutAdaptation(this);
    else
        return false;
}
