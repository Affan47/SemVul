roundup_to_power_radix ( int radix, int size, int *n_lvls )
{
    int n_levels=0, return_value=1;
    int result;
    if( 1 > size ) {
        return 0;
    }

    result=size-1;
    while (0 < result ) {
        result/=radix;
        n_levels++;
        return_value*=radix;
    };
    *n_lvls=n_levels;
    return return_value;
}
