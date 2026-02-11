GetLOD(double &in,double &out,double &wid) const
{
    if (!isValid()) return false;
    in = switchIn;
    out = switchOut;
    wid = width;
    return true;
}
