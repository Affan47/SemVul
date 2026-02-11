sg_Gap( gSensor const & front, gSensor const & side, eCoord const & dir, REAL norm, REAL def, REAL & tolerance )
{
    if ( side.ehit && side.ehit->Other() )
    {


        REAL gap1 = ( front.ehit->Vec()*( *side.ehit->Point() - *front.ehit->Point() ) )/norm;
        REAL gap2 = ( front.ehit->Vec()*( *side.ehit->Other()->Point() - *front.ehit->Point() ) )/norm;


        REAL sign = (dir * front.ehit->Vec())/norm;
        if ( sign != 0 )
        {
            sign = 1/sign;
            gap1 *= sign;
            gap2 *= sign;
        }


        tolerance = ( fabs(gap1) + fabs(gap2) ) * EPS * 10;
        REAL minGap = gap1 < gap2 ? gap1 : gap2;

        return minGap;
    }
    else
    {

        tolerance = EPS * 10 * front.hit;
        return def;
    }
}
