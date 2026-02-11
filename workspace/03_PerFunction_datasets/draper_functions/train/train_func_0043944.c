cleanup_selection( void )
{
    FL_OBJECT *obj,
              *begobj = NULL;
    int i,
        tt,
        sel = -1;

    if ( cur_form == NULL )
    {
        selnumb = 0;
        backf = FL_FALSE;
        return;
    }


    obj = cur_form->first;
    while ( obj != NULL )
    {
        if ( obj->objclass == FL_BEGIN_GROUP )
        {
            sel = 1;
            begobj = obj;
        }
        else if ( obj->objclass == FL_END_GROUP )
        {
            if ( sel )
            {
                selobj[ selnumb++ ] = begobj;
                selobj[ selnumb++ ] = obj;
            }
            else
            {
                if ( ( tt = find_selobject( begobj ) ) != -1 )
                    selobj[ tt ] = NULL;
                if ( ( tt = find_selobject( obj ) ) != -1 )
                    selobj[ tt ] = NULL;
            }
        }
        else
        {
            if ( find_selobject( obj ) == -1 )
                sel = 0;
        }

        obj = obj->next;
    }


    tmpnumb = 0;
    for ( obj = cur_form->first; obj != NULL; obj = obj->next )
        if ( find_selobject( obj ) != -1 )
            tmpobj[ tmpnumb++ ] = obj;

    for ( i = 0; i < tmpnumb; i++ )
        selobj[ i ] = tmpobj[ i ];

    selnumb = tmpnumb;
    fillin_groups( );
}
