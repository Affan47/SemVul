fl_set_formbrowser_yoffset( FL_OBJECT * ob,
                            int         offset )
{
    FLI_FORMBROWSER_SPEC *sp;
    int current;
    int h,
        f;

    if ( ! IsFormBrowserClass( ob ) )
        M_err( "fl_set_formbrowser_yoffset", "%s not a formbrowser",
               ob ? ob->label : "null" );

    sp = ob->spec;

    if ( sp->max_height < sp->canvas->h )
        offset = 0;
    if ( offset < 0 )
        offset = 0;
    if ( offset > sp->max_height - sp->canvas->h )
        offset = sp->max_height - sp->canvas->h;

    current = fl_get_formbrowser_yoffset( ob );

    h = sp->max_height;
    for ( f = sp->nforms - 1; f >= 0 && offset < h; f-- )
        h -= sp->form[ f ]->h;

    sp->top_form = ++f;
    sp->top_edge = offset - h;

    sp->old_vval = ( double ) offset / ( sp->max_height - sp->canvas->h );
    fl_set_scrollbar_value( sp->vsl, sp->old_vval );

    return current;
}
