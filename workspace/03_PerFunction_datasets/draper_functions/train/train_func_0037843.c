alerp( ConstReal aa, ConstReal bb, ConstReal fract )
{


    Real a = a_range_reduction( aa );
    Real b = a_range_reduction( bb );
    Real delta = b - a;
    if (delta > HALF_ROTATION) {
        delta -= ONE_ROTATION;
    } else if (delta < -HALF_ROTATION) {
        delta += ONE_ROTATION;
    }
    return a_range_reduction( a + delta*fract );
}
