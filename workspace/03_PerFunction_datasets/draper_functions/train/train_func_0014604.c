fl_set_spinner_value( FL_OBJECT * obj,
                      double      val )
{
    FLI_SPINNER_SPEC *sp = obj->spec;
    int max_len = 4 + sp->prec + log10( DBL_MAX );
    char buf[ max_len ];

    if ( obj->type == FL_INT_SPINNER )
    {
        sp->i_val = FL_nint( val );

        if ( val > sp->i_max )
            sp->i_val = sp->i_max;
        else if ( val < sp->i_min )
            sp->i_val = sp->i_min;

        sprintf( buf, "%d", sp->i_val );
        fl_set_input( sp->input, buf );

        return sp->old_ival = sp->i_val;
    }

    sp->f_val = val;

    if ( val > sp->f_max )
        sp->f_val = sp->f_max;
    else if ( val < sp->f_min )
        sp->f_val = sp->f_min;

    sprintf( buf, "%.*f", sp->prec, sp->f_val );
    fl_set_input( sp->input, buf );

    return sp->old_fval = sp->f_val;
}
