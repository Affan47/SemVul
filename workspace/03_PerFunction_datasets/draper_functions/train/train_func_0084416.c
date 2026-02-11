unionOrAssign(const IntRange& other, bool& union_)
{
    if (!union_ || imin > other.imin)
        imin = other.imin;
    if (!union_ || imax < other.imax)
        imax = other.imax;
    union_ = true;
}
