find_ybounds( FLI_XYPLOT_SPEC * sp )
{
    if ( sp->yautoscale )
        get_min_max( *sp->y, *sp->n, &sp->ymin, &sp->ymax );

    if ( sp->ymax - sp->ymin == 0.0 )
    {
        sp->ymin -= 1.0;
        sp->ymax += 1.0;
    }
}
