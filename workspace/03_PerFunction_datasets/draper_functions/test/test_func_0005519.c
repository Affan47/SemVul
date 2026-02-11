set_x_scale(double scale_percent)
{
    double xscale = scale_percent / 100.0;

    if (xscale != 0.0 && _xscale != 0.0)
    {
        if (scale_percent * _xscale < 0.0)
        {
            xscale = -std::abs(xscale);
        }
        else xscale = std::abs(xscale);
    }

    _xscale = scale_percent;


    SWFMatrix m = getMatrix(*this);

    m.set_x_scale(xscale);

    setMatrix(m);

    transformedByScript();
}
