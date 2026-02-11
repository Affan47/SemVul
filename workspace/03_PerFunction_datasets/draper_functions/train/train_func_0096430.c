moveVariationDown(MoveId moveId)
{
    if(isMainline())
    {
        return;
    }

    MoveId variation = variationNumber(moveId);
    MoveId parentNode = m_moveNodes[moveId].parentNode;

    QList <MoveId>& v = m_moveNodes[parentNode].variations;
    int i = v.indexOf(variation);
    if(i >= 0 && (i + 1) < v.count())
    {
        v.swap(i, i + 1);
        setModified(true);
    }
}
