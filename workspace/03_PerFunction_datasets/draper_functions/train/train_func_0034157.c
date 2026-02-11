setTotalAngle( double angle )
{
    if ( angle < 0.0 )
        angle = 0.0;

    d_data->totalAngle = angle;
    update();
}
