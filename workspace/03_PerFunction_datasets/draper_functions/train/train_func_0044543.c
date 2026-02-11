promoteVariation(MoveId variation)
{
    if(isMainline(variation))
    {
        return false;
    }

    MoveId currentNode = m_currentNode;


    while(!atLineStart(variation))
    {
        variation = m_moveNodes[variation].previousNode;
    }
    MoveId parent = m_moveNodes[variation].parentNode;


    reparentVariation(m_moveNodes[parent].nextNode, parent);

    reparentVariation(variation, m_moveNodes[parent].parentNode);


    int index = m_moveNodes[parent].variations.indexOf(variation);
    qSwap(m_moveNodes[parent].nextNode, m_moveNodes[parent].variations[index]);

    moveToId(currentNode);
    return true;
}
