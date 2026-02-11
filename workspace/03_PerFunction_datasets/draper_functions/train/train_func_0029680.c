fl_set_slider_size( FL_OBJECT * ob,
                    double      size )
{
    FLI_SLIDER_SPEC *sp = ob->spec;
    double dim;
    int min_knob = IS_SCROLLBAR( ob ) ? MINKNOB_SB : MINKNOB_SL;
    double old;

    if ( size <= 0.0 )
        size = 0.0;
    else if (size >= 1.0)
        size = 1.0;

    old = size;


    dim = IS_VSLIDER( ob ) ? ob->h : ob->w;
    dim -= 2 * FL_abs( ob->bw );
    if ( dim * size < min_knob && dim > 0.0 )
        size = min_knob / dim;

    if ( size != sp->slsize )
    {
        sp->slsize = size;
        fl_redraw_object( ob );
    }
}
