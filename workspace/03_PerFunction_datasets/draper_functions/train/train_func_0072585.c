fl_set_xyplot_return( FL_OBJECT    * obj,
                      unsigned int   when )
{
    if ( obj->type == FL_ACTIVE_XYPLOT )
        obj->how_return = when ? FL_RETURN_CHANGED : FL_RETURN_END_CHANGED;
    else
        obj->how_return = FL_RETURN_NONE;
}
