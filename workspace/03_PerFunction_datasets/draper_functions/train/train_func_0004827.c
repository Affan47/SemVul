R3Contains(const R3Cylinder& cylinder, const R3Point& point)
{

    const R3Span& axis = cylinder.Axis();


    RNScalar t = axis.T(point);
    if (RNIsNegative(t) || RNIsGreater(t, axis.Length()))
        return FALSE;


    RNLength d = R3Distance(point, axis.Point(t));
    return (RNIsLessOrEqual(d, cylinder.Radius()));
}
