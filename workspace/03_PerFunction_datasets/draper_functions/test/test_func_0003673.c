fl_set_thumbwheel_bounds( FL_OBJECT * ob,
                          double      min,
                          double      max )
{
    FLI_THUMBWHEEL_SPEC *sp;

#if FL_DEBUG >= ML_ERR
    if ( ! IsValidClass( ob, FL_THUMBWHEEL ) )
    {
        M_err( "fl_set_thumbwheel_bounds", "%s is not a thumbwheel",
               ob ? ob->label : "null" );
        return;
    }
#endif

    sp = ob->spec;
    if ( sp->min != min || sp->max != max )
    {
        sp->min = min;
        sp->max = max;
        sp->val = FL_clamp( sp->val, min, max );
        fl_redraw_object( ob );
    }

}
