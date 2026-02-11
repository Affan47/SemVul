fli_hide_composite( FL_OBJECT * obj,
                    Region    * reg )
{
    for ( obj = obj->child; obj; obj = obj->nc )
    {
        if ( obj->child )
            fli_hide_composite( obj, reg );

        fli_hide_and_get_region( obj, reg );
    }
}
