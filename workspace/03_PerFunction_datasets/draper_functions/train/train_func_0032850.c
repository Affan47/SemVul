setAxisLabelRotation( int axisId, double rotation )
{
    if ( axisValid( axisId ) )
        axisWidget( axisId )->setLabelRotation( rotation );
}
