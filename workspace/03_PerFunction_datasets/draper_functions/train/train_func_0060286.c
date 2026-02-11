deltaHue(double to, double from, unsigned int steps)
{
    double diff = fmod(to - from, 360.0) / steps;

    if (diff <= -180.0) return diff + 360.0;
    if (diff >   180.0) return diff - 360.0;
    return diff;
}
