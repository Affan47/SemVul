execute( vector< string > & argv,
                                             string & out )
{
    char buf[16];

    if( caller->current_vm == NULL )
    {
        out += "error: no VM to save\n";
        return -1;
    }

    caller->vms.push_back( caller->current_vm->copy() );

#ifndef __PLATFORM_WIN32__
    snprintf( buf, 16, "%u", caller->vms.size() - 1 );
#else
    sprintf( buf, "%u", caller->vms.size() - 1 );
#endif

    out += caller->current_vm->fullname() + " saved as VM " + buf + "\n";

    if( argv.size() > 0 )
        out += "warning: ignoring excess arguments...\n";

    return 0;
}
