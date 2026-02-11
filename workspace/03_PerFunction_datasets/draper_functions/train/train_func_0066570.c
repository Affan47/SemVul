nodeByID(uint _id) const
{
    if (!nodes.contains(_id))
    {
        return nullLiteral;
    }
    else
    {
        return nodes.value(_id);
    }
}
