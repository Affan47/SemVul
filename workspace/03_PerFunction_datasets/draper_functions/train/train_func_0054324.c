getRules()
{
    pointsPerCell = rules->pointsPerCell();
    turnAnywhere  = rules->turnAnywhere();
    if (spriteId < 1) {
        kDebug() << "pointsPerCell" << pointsPerCell
                 << "turnAnywhere" << turnAnywhere;
    }
}
