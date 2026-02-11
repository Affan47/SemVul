sp_color_wheel_process_in_triangle( SPColorWheel *wheel, gdouble x, gdouble y )
{


    Geom::Point delta( x - (((gdouble)(wheel->_triPoints[1].x + wheel->_triPoints[2].x)) / 2.0),
                     y - (((gdouble)(wheel->_triPoints[1].y + wheel->_triPoints[2].y)) / 2.0) );

    gdouble rot = (M_PI * 2 * wheel->_hue );

    Geom::Point result = delta * Geom::Rotate(rot);

    gdouble sat = CLAMP( result[Geom::X] / (wheel->_inner * 1.5), 0.0, 1.0 );

    gdouble halfHeight = (wheel->_inner * sin(M_PI/3.0)) * (1.0 - sat);
    gdouble value = CLAMP( ((result[Geom::Y]+ halfHeight) / (2.0*halfHeight)), 0.0, 1.0 );

    wheel->_triDirty = TRUE;

    sp_color_wheel_set_sv( wheel, sat, value );
}
