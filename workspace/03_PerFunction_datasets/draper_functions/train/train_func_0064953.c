round_yminmax( FLI_XYPLOT_SPEC * sp )
{

    if ( sp->yscale != FL_LOG )
    {
        float ymin = sp->ymin,
              ymax = sp->ymax,
              tic = sp->ytic;
        float threshold = 0.7 * tic;

        if ( YRound( sp ) )
        {
            ymin = ( ymin < ymax ? floor : ceil )( ymin / tic ) * tic;

            if ( FL_abs( ymin - sp->ymin ) > threshold )
                ymin = sp->ymin;

            ymax = ( ymin < ymax ? ceil : floor )( ymax / tic ) * tic;

            if ( FL_abs( ymax - sp->ymax ) > threshold )
                ymax = sp->ymax;
        }

        sp->yscmin = ymin;
        sp->yscmax = ymax;
    }
    else
    {
        float lmax = log10( sp->ymax ) / sp->lybase;
        float lmin = log10( sp->ymin ) / sp->lybase;

        if ( YRound( sp ) )
        {
            lmin = ( sp->ymin < sp->ymax ? floor : ceil )
                ( log10( sp->ymin ) / ( sp->lybase * sp->ytic ) ) * sp->ytic;
            lmax = ( sp->xmin < sp->xmax ? ceil : floor )
                ( log10( sp->ymax ) / ( sp->lybase * sp->ytic ) ) * sp->ytic;
        }

        sp->yscmin = lmin;
        sp->yscmax = lmax;
    }
}
