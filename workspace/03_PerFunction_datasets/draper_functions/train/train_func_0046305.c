roundFreq(qint64 freq, int resolution)
{
    qint64 delta = resolution;
    qint64 delta_2 = delta/2;
    if (freq >= 0)
        return ( freq - (freq+delta_2)%delta + delta_2);
    else
        return ( freq - (freq+delta_2)%delta - delta_2);
}
