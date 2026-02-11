compute_bottom_position( FL_OBJECT * ob )
{
    FLI_TABFOLDER_SPEC *sp;
    FL_OBJECT *tab;
    int i,
        max_h = 4,
        absbw = FL_abs( ob->bw );

    sp = ob->objclass == FL_TABFOLDER ? ob->spec:ob->u_vdata;
    sp->x = ob->x;

    if ( sp->nforms == 0 )
    {
        int junk;
        get_tabsize( ob, "AjbY", &junk, &max_h, -1 );
    }

    for ( i = 0; i < sp->nforms; i++ )
    {
        tab = sp->title[ i ];
        get_tabsize( ob, tab->label, &tab->w, &tab->h, -1 );
        if ( tab->h > max_h )
            max_h = tab->h;
        tab->x = sp->x;
        fli_inherit_attributes( ob, tab );
        sp->x += tab->w + ( ob->bw > 0 );
    }

    sp->canvas->h = ob->h - 2 * absbw - max_h - 1;
    sp->y = sp->canvas->y + sp->canvas->h + absbw - ( ob->bw < 0 );

    for ( i = 0; i < sp->nforms; i++ )
    {
        sp->title[ i ]->h = max_h;
        sp->title[ i ]->y = sp->y;
    }

    sp->max_h = max_h;
    fl_set_object_color( sp->canvas, ob->col1, ob->col2 );
}
