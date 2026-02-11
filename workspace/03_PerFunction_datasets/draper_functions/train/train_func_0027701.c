axis_to_image(mosca::axis an_axis) const
{
    mosca::axis image_axis;


    if(an_axis == mosca::DISPERSION_AXIS)
        image_axis = dispersion_axis();
    else if(an_axis == mosca::SPATIAL_AXIS)
        image_axis = spatial_axis();
    else
        image_axis = an_axis;

    return image_axis;
}
