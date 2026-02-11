createScaledImage(const signed long left_pos,
                                          const signed long top_pos,
                                          unsigned long width,
                                          unsigned long height,
                                          const double xfactor,
                                          const double yfactor,
                                          const int interpolate,
                                          const int aspect,
                                          const Uint16 pvalue) const
{
    if ((xfactor >= 0) && (yfactor >= 0))
    {
        const unsigned long gw = getWidth();
        const unsigned long gh = getHeight();
        if ((width == 0) && (left_pos < OFstatic_cast(signed long, gw)))
            width = gw - left_pos;
        if ((height == 0) && (top_pos < OFstatic_cast(signed long, gh)))
            height = gh - top_pos;
        return createScaledImage(left_pos, top_pos, width, height, OFstatic_cast(unsigned long, xfactor * width),
            OFstatic_cast(unsigned long, yfactor * height), interpolate, aspect, pvalue);
    }
    return NULL;
}
