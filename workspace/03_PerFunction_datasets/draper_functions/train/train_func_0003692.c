handle_motion( FL_OBJECT * obj,
               FL_Coord    mx,
               FL_Coord    my,
               int         key,
               void      * ev )
{
    FLI_SLIDER_SPEC *sp = obj->spec;
    int ret;


    if (    IS_SCROLLBAR( obj )
         && sp->mouse_off_knob
         && key )
        return FL_RETURN_NONE;


    if ( key != FL_MBUTTON1 )
    {
        int old_state = sp->mouse_off_knob;

        sp->mouse_off_knob = is_off_knob( obj, mx, my );

        if ( old_state != sp->mouse_off_knob )
        {
            sp->mouse = sp->mouse_off_knob ? FLI_SLIDER_NONE : FLI_SLIDER_KNOB;
            fl_redraw_object( obj );
        }

        return FL_RETURN_NONE;
    }


    if ( ! IS_SCROLLBAR( obj ) )
    {
        if ( shiftkey_down( ( ( XEvent * ) ev )->xmotion.state ) )
        {
            if ( ! sp->was_shift )
            {
                sp->old_mx = mx;
                sp->old_my = my;
                sp->was_shift = 1;
            }

            if ( IS_HSLIDER( obj ) )
                mx = sp->old_mx + ( mx - sp->old_mx ) * FL_SLIDER_FINE;
            else
                my = sp->old_my + ( my - sp->old_my ) * FL_SLIDER_FINE;
        }
        else
            sp->was_shift = 0;
    }

    if (    ( ret = handle_mouse( obj, mx, my, key ) )
         && ! ( obj->how_return & FL_RETURN_END_CHANGED ) )
        sp->start_val = sp->val;

    return ret;
}
