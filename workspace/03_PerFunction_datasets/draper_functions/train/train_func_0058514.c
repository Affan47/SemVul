handle_applresdir( const char * rstr,
                   const char * appclass )
{
    char *tok;
    char rbuf[ 512 ],
         buf[ 512 ];
    XrmDatabase fdb = 0;

    strcpy( rbuf, rstr );
    for ( tok = strtok( rbuf, ":" ); tok; tok = strtok( 0, ":" ) )
    {
        fl_snprintf( buf, sizeof buf,"%s/%s", tok,appclass );
        M_info( "handle_applresdir", "Trying XAPPLRESDIR: %s", buf );
        if ( ( fdb = XrmGetFileDatabase( buf ) ) )
        {
            XrmMergeDatabases( fdb, &fldatabase );
            M_warn( "handle_applresdir", "XAPPLRESDIR %s loaded", buf );
        }
    }
}
