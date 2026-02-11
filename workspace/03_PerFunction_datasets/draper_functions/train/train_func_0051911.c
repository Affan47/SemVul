fl_get_object_component( FL_OBJECT * composite,
                         int         objclass,
                         int         type,
                         int         numb )
{
    FL_OBJECT *tmp;
    int n;

    for ( n = 0, tmp = composite->child; tmp; tmp = tmp->nc )
        if ( tmp->objclass == objclass && ( tmp->type == type || type < 0 ) )
        {
            if ( ++n >= numb )
                return tmp;
        }

    M_err( "fl_get_object_component", "Requested object not found" );

    return NULL;
}
