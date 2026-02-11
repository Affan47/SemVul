lgl_units_get_units_per_point (lglUnits     units)
{
        if ( (units >= LGL_UNITS_FIRST) && (units <= LGL_UNITS_LAST) )
        {
                return 1.0 / unit_table[units].points_per_unit;
        }
        else
        {

                return 1.0;
        }
}
