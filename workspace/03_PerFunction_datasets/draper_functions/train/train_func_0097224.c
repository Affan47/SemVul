tabSide(const QStyleOptionTab* tbOpt) const
{
    switch (tbOpt->shape)
    {
    case QTabBar::RoundedEast:
    case QTabBar::TriangularEast:
        return East;
    case QTabBar::RoundedWest:
    case QTabBar::TriangularWest:
        return West;
    case QTabBar::RoundedNorth:
    case QTabBar::TriangularNorth:
        return North;
    default:
        return South;
    }
}
