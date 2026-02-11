set_xyplot_attrib( FL_OBJECT * ob )
{
    xyplot_attrib->vdata = ob;
    xyplot_spec = get_superspec(ob);

    if ( ob->type != FL_ACTIVE_XYPLOT )
    {
        fl_hide_object( xyplot_attrib->how_return );
        fl_hide_object( xyplot_attrib->mark_active );
    }
    else
    {
        fl_show_object( xyplot_attrib->how_return );
        fl_show_object( xyplot_attrib->mark_active );
    }

    if ( xyplot_spec->xscale != FL_LOG )
        fl_hide_object( xyplot_attrib->xbase );
    else
        fl_show_object( xyplot_attrib->xbase );

    if ( xyplot_spec->yscale != FL_LOG )
        fl_hide_object( xyplot_attrib->ybase );
    else
        fl_show_object( xyplot_attrib->ybase );

    if ( xyplot_spec->xgrid || xyplot_spec->ygrid )
        fl_show_object( xyplot_attrib->gridstyle );
    else
        fl_hide_object( xyplot_attrib->gridstyle );

    show_spec( xyplot_spec );

    return 0;
}
