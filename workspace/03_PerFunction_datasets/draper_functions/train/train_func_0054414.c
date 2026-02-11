ClosestPoint(const R2Point& point) const
{

    R2Point closest(point);
    if (closest.X() < XMin()) closest[RN_X] = XMin();
    else if (closest.X() > XMax()) closest[RN_X] = XMax();
    if (closest.Y() < YMin()) closest[RN_Y] = YMin();
    else if (closest.Y() > YMax()) closest[RN_Y] = YMax();
    return closest;
}
