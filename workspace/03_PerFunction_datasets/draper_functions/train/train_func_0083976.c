fl_set_browser_hscrollbar( FL_OBJECT * obj,
                           int         on )
{
    FLI_BROWSER_SPEC *comp = obj->spec;

    if ( comp->h_pref != on )
    {
        comp->h_pref = on;
        redraw_scrollbar( obj );
        fli_tbox_react_to_hori( comp->tb, on != FL_OFF );
        get_geometry( obj );
        fl_redraw_object( obj );
    }
}
