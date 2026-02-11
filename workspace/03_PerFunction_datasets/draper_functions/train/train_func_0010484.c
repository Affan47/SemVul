value(float n1, float n2, float hue)
{
    float v;

    if (hue > 360.0)
        hue -= 360.0;
    if (hue < 0.0)
        hue += 360.0;
    if (hue < 60.0) {
        v = n1 + (n2 - n1) * hue / 60.0;
    }
    else {
        if (hue < 180.0)
            v = n2;
        else {
            if (hue < 240.0)
                v = n1 + (n2 - n1) * (240.0 - hue) / 60.0;
            else
                v = n1;
        }
    }
    return (v);
}
