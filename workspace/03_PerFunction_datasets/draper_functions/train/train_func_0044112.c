operator==(const VertID& rhs) const
{
    if ((objID != rhs.objID) || (vn != rhs.vn))
    {
        return false;
    }


    return true;
}
