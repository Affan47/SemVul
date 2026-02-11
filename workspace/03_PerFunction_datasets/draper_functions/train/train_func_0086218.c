run()
{

    EM_log( CK_LOG_SYSTEM, "running chuck shell..." );


    if(initialized == FALSE)
    {
        fprintf( stderr, "[chuck](via shell): shell not initialized...\n" );
        return;
    }

    string command;
    string result;

    ui->next_result( "welcome to chuck shell!\n" );


    for( ; !stop; )
    {

        if( ui->next_command( prompt, command ) == TRUE )
        {

            result = "";


            execute( command, result );


            command = "";


            ui->next_result( result );
        }
        else

            break;
    }


    EM_log( CK_LOG_SYSTEM, "exiting chuck shell..." );
}
