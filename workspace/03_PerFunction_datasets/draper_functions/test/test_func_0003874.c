numberOfSiblings(MoveId moveId) const
{
    MoveId node = nodeValid(moveId);
    if(node == NO_MOVE)
    {
        return 0;
    }
    MoveId parentNode = m_moveNodes[node].parentNode;
    if(parentNode == NO_MOVE)
    {
        return 0;
    }
    return m_moveNodes[parentNode].variations.size();
}
