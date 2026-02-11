setMass( double val )
{
    if ( val < 0.001 )
        d_data->mass = 0.0;
    else if ( val > 100.0 )
        d_data->mass = 100.0;
    else
        d_data->mass = val;
}
