read_tiff_field
                ( int        fh,
                  TiffField  *fld,
                  Error      (*rs)(int,uint16*),
                  Error      (*rl)(int,uint32*) )
{
    int i;
    int save;

    DXASSERTGOTO ( fh  >  0 );
    DXASSERTGOTO ( fld != ERROR );
    DXASSERTGOTO ( rs  != ERROR );
    DXASSERTGOTO ( rl  != ERROR );

    if ( !rs ( fh, &fld->tag    ) ||
         !rs ( fh, &fld->type   ) ||
         !rl ( fh, &fld->length )   )
        goto error;

    if ( 0 > ( save = lseek ( fh, 0, 1 ) ) )
        DXErrorGoto2
            ( ERROR_DATA_INVALID,
              "#11800",
              "lseek()" )
    else
        save += 4;

    DXDebug ( "R",
              "tag,type,length = %d %s, %d %s, %d",
              fld->tag,  ( tiff_lookup ( (TiffTag) fld->tag ) ) -> tag_name,
              fld->type, ((fld->type>=1)&&(fld->type<=5)) ?
                             tiff_type_name [ fld->type ] :
                             "** Error **",
              fld->length );

    if ( ( tiff_type_bytecount [ fld->type ] * fld->length ) > 4 )
        { if ( !rl ( fh, &fld->value.offset ) ) goto error; }
    else
        switch ( fld->type )
        {
            case tiff_BYTE:
            case tiff_ASCII:
                if (read ( fh, &fld->value.value, fld->length ) != fld->length )
                    DXErrorGoto2
                        ( ERROR_DATA_INVALID,
                          "#11800",

                          "read()" );
                break;

            case tiff_SHORT:
                for ( i=0; i<fld->length; i++ )
                    if ( !rs ( fh, &((uint16*)&fld->value.value)[i] ) )
                        goto error;
                break;

            case tiff_LONG:
                if ( !rl ( fh, &fld->value.value ) )
                    goto error;
                break;
        }

    if ( 0 > lseek ( fh, save, 0 ) )
        DXErrorGoto2
            ( ERROR_DATA_INVALID,
              "#10911",
              save );

    return fld;

    error:
        return ERROR;
}
