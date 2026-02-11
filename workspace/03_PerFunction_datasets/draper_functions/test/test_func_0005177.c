calc_mouse_obj( FL_OBJECT * ob,
                FL_Coord    mx,
                FL_Coord    my )
{
    FLI_COUNTER_SPEC *sp = ob->spec;

    sp->mouseobj = NONE;

    if ( my < ob->y || my > ob->y + ob->h || mx < ob->x )
        return;


    if ( ob->type == FL_NORMAL_COUNTER )
    {
        if ( mx < ob->x + sp->ww[ 0 ] )
            sp->mouseobj = OB0;
        else if ( mx < sp->ww[ 1 ] + sp->xx[ 1 ] )
            sp->mouseobj = OB1;
        else if ( mx < sp->ww[ 4 ] + sp->xx[ 4 ] )
            sp->mouseobj = OB4;
        else if ( mx < sp->ww[ 2 ] + sp->xx[ 2 ] )
            sp->mouseobj = OB2;
        else if ( mx < sp->ww[ 3 ] + sp->xx[ 3 ] )
            sp->mouseobj = OB3;
    }
    else
    {


        if ( mx < ob->x + sp->ww[ 1 ] )
            sp->mouseobj = OB1;
        else if ( mx < sp->xx[ 4 ] + sp->ww[ 4 ] )
            sp->mouseobj = OB4;
        else if ( mx < sp->xx[ 2 ] + sp->ww[ 2 ] )
            sp->mouseobj = OB2;
    }
}
