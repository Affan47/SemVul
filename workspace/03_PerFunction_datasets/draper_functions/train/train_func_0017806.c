fl_set_browser_scrollbarsize( FL_OBJECT * ob,
                              int         hh,
                              int         vw )
{
    FLI_BROWSER_SPEC *comp = ob->spec;
    int redraw = 0;

    if ( hh > 0 && hh != comp->hsl->h )
    {
        comp->hsl->h = comp->hh_def = hh;
        redraw = 1;
    }

    if ( vw > 0 && vw != comp->vsl->w )
    {
        comp->vsl->w = comp->vw_def = vw;
        redraw = 1;
    }

    if ( redraw )
    {
        comp->user_set = 1;
        fl_redraw_object( ob );
        fl_redraw_object( comp->tb );
        fl_redraw_object( comp->hsl );
        fl_redraw_object( comp->vsl );
    }
}
