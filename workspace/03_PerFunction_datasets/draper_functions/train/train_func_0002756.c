R3Distance(const R3Point& point, const R3Span& span)
{

    R3Vector v1 = point - span.Start();
    RNScalar dir1 = v1.Dot(span.Vector());
    if (RNIsNegative(dir1)) return v1.Length();


    R3Vector v2 = point - span.End();
    RNScalar dir2 = v2.Dot(span.Vector());
    if (RNIsPositive(dir2)) return v2.Length();


    return R3Distance(point, span.Line());
}
