atLineEnd(MoveId moveId) const
{
    MoveId node = nodeValid(moveId);
    if(node != NO_MOVE)
    {
        if(m_moveNodes[node].nextNode == NO_MOVE)
        {
            return true;
        }
    }

    return false;
}
