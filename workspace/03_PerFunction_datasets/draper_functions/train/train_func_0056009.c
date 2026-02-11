ParseAsciiNum (
    const MIDISystemExclusive *e,
    int *pos,
    MIDICue *num )
{
    ulong v;
    uchar c;
    bool f;

    c = e->GetData ( *pos );

    if ( c == 0xf7 )
    {

        return false;
    }

    f = ParseAsciiNum ( e, pos, &v );

    if ( f )
    {
        num->SetNumValues ( 1 );
        num->SetV1 ( v );
    }


    c = e->GetData ( *pos );

    if ( c == '.' )
    {


        ( *pos ) ++;
        f = ParseAsciiNum ( e, pos, &v );

        if ( f )
        {
            num->SetNumValues ( 2 );
            num->SetV2 ( v );
        }


        c = e->GetData ( *pos );

        if ( c == '.' )
        {


            ( *pos ) ++;
            f = ParseAsciiNum ( e, pos, &v );

            if ( f )
            {
                num->SetNumValues ( 2 );
                num->SetV3 ( v );
            }


            c = e->GetData ( *pos );

            if ( c == '.' )
            {


                while ( *pos < e->GetLengthSE() )
                {
                    c = e->GetData ( ( *pos ) );

                    if ( c == 0xf7 || c == 0x00 )
                    {
                        break;
                    }

                    ( *pos ) ++;
                }
            }
        }
    }

    while ( ++ ( *pos ) < e->GetLengthSE() )
    {
        if ( e->GetData ( *pos ) != 0 )
            break;
    }

    return f;
}
