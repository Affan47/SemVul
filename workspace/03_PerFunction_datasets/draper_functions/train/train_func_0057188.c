isClose( SPColor const& other, float epsilon ) const
{
    bool match = false;

    match = (fabs((v.c[0]) - (other.v.c[0])) < epsilon)
        && (fabs((v.c[1]) - (other.v.c[1])) < epsilon)
        && (fabs((v.c[2]) - (other.v.c[2])) < epsilon);

    match &= profileMatches( icc, other.icc );

    return match;
}
