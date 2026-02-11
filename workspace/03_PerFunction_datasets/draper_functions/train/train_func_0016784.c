flatten_cf_mg ( Object in, MultiGrid out, int *position )
{
    Object child;
    int    i;


    DXASSERTGOTO ( in && out && position );

    switch ( DXGetObjectClass ( in ) )
    {
        case CLASS_FIELD:
            if ( !DXSetEnumeratedMember ( (Group)out, *position, in ) )
                goto error;

            (*position)++;
            break;

        case CLASS_GROUP:
            for ( i     = 0;
                  NULL != ( child = DXGetEnumeratedMember
                                        ( (Group)in, i, NULL ) );
                  i++ )
                if ( !flatten_cf_mg ( child, out, position ) )
                    goto error;
            break;

        default:
            DXErrorGoto
                ( ERROR_DATA_INVALID, "Illegal member in Composite Field" );
    }

    return (Object) out;

    error:
        DXASSERT ( DXGetError() != ERROR_NONE );
        return ERROR;
}
