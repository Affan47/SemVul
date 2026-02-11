attachGradientBevelFilterInterface(as_object& o)
{
    const int flags = PropFlags::onlySWF8Up;
    o.init_property("distance", gradientbevelfilter_distance,
        gradientbevelfilter_distance, flags);
    o.init_property("angle", gradientbevelfilter_angle,
        gradientbevelfilter_angle, flags);
    o.init_property("alphas", gradientbevelfilter_alphas,
        gradientbevelfilter_alphas, flags);
    o.init_property("colors", gradientbevelfilter_colors,
        gradientbevelfilter_colors, flags);
    o.init_property("ratios", gradientbevelfilter_ratios,
        gradientbevelfilter_ratios, flags);
    o.init_property("blurX", gradientbevelfilter_blurX,
        gradientbevelfilter_blurX, flags);
    o.init_property("blurY", gradientbevelfilter_blurY,
        gradientbevelfilter_blurY, flags);
    o.init_property("strength", gradientbevelfilter_strength,
        gradientbevelfilter_strength, flags);
    o.init_property("quality", gradientbevelfilter_quality,
        gradientbevelfilter_quality, flags);
    o.init_property("type", gradientbevelfilter_type,
        gradientbevelfilter_type, flags);
    o.init_property("knockout", gradientbevelfilter_knockout,
        gradientbevelfilter_knockout, flags);

}
