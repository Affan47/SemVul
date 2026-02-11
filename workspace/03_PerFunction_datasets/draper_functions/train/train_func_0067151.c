init_shell( Chuck_Shell * shell, Chuck_Shell_UI * ui, Chuck_VM * vm )
{

    if( !ui->init() )
    {
        fprintf( stderr, "[chuck]: error starting shell UI...\n" );
        return FALSE;
    }


    if( !shell->init( vm, ui ) )
    {
        fprintf( stderr, "[chuck]: error starting shell...\n" );
        return FALSE;
    }

    return TRUE;
}
