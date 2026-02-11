add_type_def( int  cn,
              int  tn,
              char name[ ] )
{
    int i;

    if ( tn >= MAXTYPES || tn < 0 )
    {
        M_err( "add_type_def", "Bad type: %d", tn );
        return;
    }

    for ( i = 0; i < cnumb; i++ )
        if ( classes[ i ].cn == cn )
        {
            classes[ i ].types[ tn ].defined = FL_TRUE;
            strcpy( classes[ i ].types[ tn ].tname, name );
        }
}
