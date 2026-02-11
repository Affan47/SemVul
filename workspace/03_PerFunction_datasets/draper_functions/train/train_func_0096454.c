variationCount(MoveId moveId) const
{
    MoveId node = nodeValid(moveId);
    if(node != NO_MOVE)
    {
        return m_moveNodes[node].variations.size();
    }
    return 0;
}
