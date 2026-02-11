triple_prod( double a[], double b[], double c[], double *sine_value )
{
    double ab[3], dot_prod_ab_c, abs_c, abs_ab;
    cross_prod3( a, b, ab );


    dot_prod_ab_c   =  dot_prod3( ab, c );

    if ( sine_value ) {
        abs_c  = len3( c );

        abs_ab = len3( ab );


        if ( abs_c > 1.e-7  && abs_ab > 1.e-7  ) {
            *sine_value = MPY_SINE * dot_prod_ab_c / ( abs_c * abs_ab);

        } else {
            *sine_value = 0.0;
        }
    }
    return dot_prod_ab_c;
}
