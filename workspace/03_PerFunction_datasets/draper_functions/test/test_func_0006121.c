expand(GridPoint & gridPoint, RouteThing & routeThing)
{


    if (gridPoint.x > 0) expandOne(gridPoint, routeThing, -1, 0, 0, false);
    if (gridPoint.x < m_grid->x - 1) expandOne(gridPoint, routeThing, 1, 0, 0, false);
    if (gridPoint.y > 0) expandOne(gridPoint, routeThing, 0, -1, 0, false);
    if (gridPoint.y < m_grid->y - 1) expandOne(gridPoint, routeThing, 0, 1, 0, false);
    if (m_bothSidesNow) {
        if (gridPoint.z > 0) expandOne(gridPoint, routeThing, 0, 0, -1, true);
        if (gridPoint.z < m_grid->z - 1) expandOne(gridPoint, routeThing, 0, 0, 1, true);
    }


}
