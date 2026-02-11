canHaveStartAnnotation(MoveId moveId) const
{
    MoveId node = nodeValid(moveId);
    return atLineStart(moveId) || atGameStart(m_moveNodes[node].previousNode);
}
